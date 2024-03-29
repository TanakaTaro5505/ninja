#include "Player.h"
#include "Game.h"
#include "Sound.h"

#include "SceneMain.h"

static constexpr int kHpBarLen = 80;
static constexpr int kHpBarHeight = 8;

static constexpr int kExpBarLen = 80;
static constexpr int kExpBarHeight = 8;
// ダメージ受けた後の無敵時間(フレーム)
static const int kDamageFrame = 60;

// 最大パワーアップ
static constexpr int kMaxPowerup[Player::kPowerupTypeNum] =
{
	4,	// kPowerupTypeShotPower,	// ショットの攻撃力、サイズ
	4,	// kPowerupTypeShotDir,		// 攻撃方向
	3,	// kPowerupTypeBackShot,	// 後方攻撃
	2,	// kPowerupTypeMoveSpeed,	// 移動速度
	4,	// kPowerupTypeShotInterval,// 発射間隔
};

// パワーアップ内容に応じたテキスト表示
static const char* const kPowerupText[Player::kPowerupTypeNum] =
{
	"手裏剣の攻撃力があがった！",			// kPowerupTypeShotPower,	// ショットの攻撃力、サイズ
	"たくさん投げられるようになった！",		// kPowerupTypeShotDir,		// 攻撃方向
	"ホーミング手裏剣を投げられるようになった！",	// kPowerupTypeBackShot,	// 後方攻撃
	"移動速度が上がった！",					// kPowerupTypeMoveSpeed,	// 移動速度
	"手裏剣の連射速度が上がった！",			// kPowerupTypeShotInterval,// 発射間隔
};

// 基本性能
static constexpr int kMaxHp			= 100;
static constexpr int kShotSpeed		= 6;
static constexpr int kDamagePrevent = 0;

// 攻撃力
static constexpr int kShotDamage = 6;
static constexpr int kShotDamagePowerup = 2;
static constexpr int kShotDamageMax = 14;

// ショットサイズ
static constexpr float kShotSize = 1.0f;
static constexpr float kShotSizePowerup = 0.25f;
static constexpr float kShotSizeMax = 2.0f;

// 移動速度
static constexpr int kMoveSpeed = 4;
static constexpr int kMoveSpeedPowerup = 1;
static constexpr int kMoveSpeedMax = 6;

// 発射間隔
static constexpr int kShotInterval = 16;
static constexpr int kShotIntervalPowerup = -2;
static constexpr int kShotIntervalMin = 8;

// レベルに応じたショットデータ
typedef struct LevelShotData
{
	int level;
	Player::ShotData	data;
}LevelShotData;

static constexpr LevelShotData	kLevelShotDataTbl[] =
{
	// lv0
	{ 0, {  0.0f,  0.0f, kShotSpeed,  0.0f, 5 } },
	// lv1
	{ 1, {  0.0f,  0.0f, kShotSpeed,  0.0f, 10 } },
	// lv2
	{ 2, { -6.0f, -6.0f, kShotSpeed,  0.0f, 8 } },
	{ 2, {  6.0f,  6.0f, kShotSpeed,  0.0f, 8 } },
	// lv3
	{ 3, {  0.0f,  0.0f, kShotSpeed,  0.0f, 6 } },
	{ 3, {  0.0f,  0.0f, kShotSpeed, 10.0f, 6 } },
	{ 3, {  0.0f,  0.0f, kShotSpeed,-10.0f, 6 } },
	// lv4
	{ 4, {  0.0f,  0.0f, kShotSpeed,  0.0f, 6 } },
	{ 4, {  0.0f,  0.0f, kShotSpeed, 10.0f, 6 } },
	{ 4, {  0.0f,  0.0f, kShotSpeed,-10.0f, 6 } },
	{ 4, {  0.0f,  0.0f, kShotSpeed,180.0f, 6 } },
};

static constexpr int kLevelShotDataTblSize = sizeof(kLevelShotDataTbl) / sizeof(kLevelShotDataTbl[0]);
// ショットの最大レベル
static constexpr int kShotLevelMax = kLevelShotDataTbl[kLevelShotDataTblSize-1].level;

// ===================================================================================
void Player::init()
{
	m_seq = Seq::kSeqMain;

	m_maxHp = kMaxHp;
	m_hp = m_maxHp;
	m_shotSpeed = kShotSpeed;
	m_damagePrevent = kDamagePrevent;

	for (int i = 0; i < kPowerupTypeNum; i++)
	{
		m_powerUp[i] = 0;
	}

	m_lastShot = 0;
	m_damageFrame = -1;

	m_level = 0;
	m_exp = 0;

	setShot(m_level);

	for (int i = 0; i < kPosLogNum; i++)
	{
		m_posLog[i] = m_pos;
	}
}

void Player::update()
{
	if (!m_isExist)	return;
	
	for (int i = kPosLogNum - 1; i >= 1; i--)
	{
		m_posLog[i] = m_posLog[i - 1];
	}
	m_posLog[0] = m_pos;

	// ゲームクリア後の演出
	if (m_seq == Seq::kSeqGameClear)
	{
		m_pos.x += getPlayerSpeed() * 2;
		return;
	}

	// 無敵時間
	m_damageFrame--;
	if (m_damageFrame < -1)	m_damageFrame = -1;

	// 移動
	bool isInput = false;
	if (Pad::isPress(PAD_INPUT_LEFT))
	{
		m_vec.x = -1.0f;
		isInput = true;
	}
	else if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		m_vec.x = 1.0f;
		isInput = true;
	}
	else
	{
		m_vec.x = 0.0f;
	}

	if (Pad::isPress(PAD_INPUT_UP))
	{
		m_vec.y = -1.0f;
		isInput = true;
	}
	else if (Pad::isPress(PAD_INPUT_DOWN))
	{
		m_vec.y = 1.0f;
		isInput = true;
	}
	else
	{
		m_vec.y = 0.0f;
	}

	if(isInput)
	{
		m_vec.normalize();
	}

	m_vec *= static_cast<float>(getPlayerSpeed());

	m_pos += m_vec;

	if (m_pos.x < 0.0f + m_radius)		m_pos.x = (0.0f + m_radius);
	if (m_pos.x > Game::cScreenWidth - m_radius)	m_pos.x = (Game::cScreenWidth - m_radius);
	if (m_pos.y < 0.0f + m_radius)		m_pos.y = (0.0f + m_radius);
	if (m_pos.y > Game::cScreenHeight - m_radius)	m_pos.y = (Game::cScreenHeight - m_radius);

	// ショット
	m_lastShot++;
	if ((Pad::isTrigger(PAD_INPUT_1)) ||
		((Pad::isPress(PAD_INPUT_1)) && (m_lastShot >= getShotInterval())))
	{
		Sound::PlaySound(Sound::kSoundID_Shot);
#if false
		for( int i= 0; i < m_shotNum; i++)
		{
			VECTOR pos = getPos();
			pos.x += m_shotData[i].startOffsetX;
			pos.y += m_shotData[i].startOffsetY;
			Shot* pShot = nullptr;
			pShot = m_pMain->createPlayerShot(pos);
			// 弾の初期設定を行う
			if (pShot)
			{
				pShot->setMoveSpeed(m_shotData[i].speed);
				pShot->setMoveAngle(m_shotData[i].angle);

				pShot->setPower(getShotDamage());
				pShot->setScale(getShotScale());
			}
		}
#else
		// 前方ショット
		int frontNum = m_powerUp[kPowerupTypeShotDir]+1;
		if (frontNum > 5)	frontNum = 5;
		int startAngle = -(frontNum-1) * 5;
		for (int i = 0; i < frontNum; i++)
		{
			Shot* pShot = nullptr;
			pShot = m_pMain->createPlayerShot(getPos());
			// 弾の初期設定を行う
			if (pShot)
			{
				pShot->setMoveSpeed(kShotSpeed);
				pShot->setMoveAngle(static_cast<float>(startAngle + i*10));
				pShot->setPower(getShotDamage());
				pShot->setScale(getShotScale());
			}
		}

		// 後方ショット
		int backNum = m_powerUp[kPowerupTypeBackShot];
		if (backNum > 3)	backNum = 3;
		startAngle = -(backNum - 1) * 5;
		for (int i = 0; i < backNum; i++)
		{
			Shot* pShot = nullptr;
			pShot = m_pMain->createPlayerShot(getPos());
			// 弾の初期設定を行う
			if (pShot)
			{
				pShot->setMoveSpeed(kShotSpeed);
				pShot->setMoveAngle(static_cast<float>(180 + startAngle + i * 10));
				pShot->setPower(getShotDamage());
				pShot->setScale(getShotScale());

				pShot->setHoming();
			}
		}
#endif
		m_lastShot = 0;
	}
}

void Player::draw()
{
	if (!m_isExist)	return;
	if (getHp() <= 0)	return;

	if( (m_damageFrame < 0) || (m_damageFrame % 2) || m_seq != Seq::kSeqMain )
	{
	//	const int kAlphaIntervel = 256 / kPosLogNum;
		const int kAlphaIntervel = 128 / kPosLogNum;
		for (int i = kPosLogNum - 1; i >= 0; i--)
		{
			int alpha = kAlphaIntervel * ((kPosLogNum - 1) - i);
			if (alpha >= 255)	alpha = 255;
			if (alpha < 0)		alpha = 0;

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
			DrawRotaGraph2(static_cast<int>(m_posLog[i].x), static_cast<int>(m_posLog[i].y),
				m_graphicSizeX / 2, m_graphicSizeY / 2,
				m_scale, m_angle,
				m_graphicHandle, true, false);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		GameObject::draw();
	}
	

	// HPゲージの表示
	if (m_maxHp <= 0)	return;

	int x1 = static_cast<int>(m_pos.x - kHpBarLen / 2);
	int x2 = static_cast<int>(m_pos.x + kHpBarLen / 2);
	int y1 = static_cast<int>(m_pos.y + 32);
	int y2 = y1 + kHpBarHeight;
	DrawBox(x1, y1, x2, y2, GetColor(0, 255, 0), false);
	x2 = x1 + kHpBarLen * m_hp / m_maxHp;
	DrawBox(x1, y1, x2, y2, GetColor(0, 255, 0), true);

	// レベル、経験値表示
	x1 = static_cast<int>(m_pos.x - kExpBarLen / 2);
	x2 = static_cast<int>(m_pos.x + kExpBarLen / 2);
	y1 = static_cast<int>(m_pos.y - 32);
	y2 = y1 + kExpBarHeight;
	DrawBox(x1, y1, x2, y2, GetColor(255, 255, 0), false);
	x2 = x1 + kExpBarLen * m_exp / getNextLevelExp();
	DrawBox(x1, y1, x2, y2, GetColor(255, 255, 0), true);

	DrawFormatString(x1 - 8, y1, GetColor(255, 255, 255), "%d", getLevel());
}

bool Player::isGetDamage()
{
	// 無敵期間中はダメージ受けない
	if (m_damageFrame >= 0)	return false;
	// ゲームクリア後などはダメージ受けない
	if( m_seq != Seq::kSeqMain )	return false;

	return true;
}

void Player::damage(int getDamage)
{
	// 無敵期間中はダメージ受けない
	if (m_damageFrame >= 0)	return;

	int dealt = getDamage;
	dealt -= m_damagePrevent;
	if (dealt < 1)	dealt = 1;

	int last = m_hp;
	m_hp -= dealt;
	m_damageFrame = kDamageFrame;

	// 死亡時処理
	if(last > 0 && m_hp <= 0)
	{
		Sound::PlaySound(Sound::kSoundID_Dead);
	}
}

// パワーアップ関連処理
void Player::addExp(int add)
{
	m_exp += add;

	// レベル上がったらパワーアップ
	if (m_exp >= getNextLevelExp())
	{
		m_exp -= getNextLevelExp();
		m_level++;

		setShot(m_level);
		Sound::PlaySound(Sound::kSoundID_Levelup);

		// パワーアップ
		int count = 0;
		int levelUpType = 0;
		while (1)
		{
			levelUpType = GetRand(kPowerupTypeNum - 1);
			if ((m_powerUp[levelUpType] < kMaxPowerup[levelUpType]) ||
				(count >= 256))
			{
				m_powerUp[levelUpType]++;
				break;
			}
			count++;
		}
		// レベルアップ演出開始
		m_pMain->setLevelup(getPos(), kPowerupText[levelUpType]);
	}
}

int Player::getLevel()
{
	return m_level;
}

int Player::getNextLevelExp()
{
	return 15 + getLevel() * 5;
}

void Player::setShot(int level)
{
	int now = level;
	if (level > kShotLevelMax) now = kShotLevelMax;

	m_shotNum = 0;

	for (int i = 0; i < kLevelShotDataTblSize; i++)
	{
		if (kLevelShotDataTbl[i].level != now)	continue;
		
		m_shotData[m_shotNum] = kLevelShotDataTbl[i].data;

		m_shotNum++;
	}
}

int Player::getShotDamage()
{
	int result = kShotDamage;
	result += kShotDamagePowerup * m_powerUp[kPowerupTypeShotPower];
	if (result > kShotDamageMax)	result = kShotDamageMax;

	return result;
}

float Player::getShotScale()
{
	float result = kShotSize;
	result += kShotSizePowerup * m_powerUp[kPowerupTypeShotPower];	// 攻撃力でサイズも変わる
	if (result > kShotSizeMax)	result = kShotSizeMax;

	return result;
}

int Player::getPlayerSpeed()
{
	int result = kMoveSpeed;
	result += kMoveSpeedPowerup * m_powerUp[kPowerupTypeMoveSpeed];
	if (result > kMoveSpeedMax)	result = kMoveSpeedMax;

	return result;
}

int Player::getShotInterval()
{
	int result = kShotInterval;
	result += kShotIntervalPowerup * m_powerUp[kPowerupTypeShotInterval];
	if (result < kShotIntervalMin)	result = kShotIntervalMin;

	return result;
}
