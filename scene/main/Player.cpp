#include "Player.h"
#include "Game.h"
#include "Sound.h"

#include "SceneMain.h"

static constexpr int kHpBarLen = 80;
static constexpr int kHpBarHeight = 8;

static constexpr int kExpBarLen = 80;
static constexpr int kExpBarHeight = 8;
// �_���[�W�󂯂���̖��G����(�t���[��)
static const int kDamageFrame = 60;

// ��{���\
static constexpr int kMaxHp			= 100;
static constexpr int kShotSpeed		= 6;
static constexpr int kDamagePrevent = 0;

// �U����
static constexpr int kShotDamage = 6;
static constexpr int kShotDamagePowerup = 2;
static constexpr int kShotDamageMax = 14;

// �V���b�g�T�C�Y
static constexpr float kShotSize = 1.0f;
static constexpr float kShotSizePowerup = 0.25f;
static constexpr float kShotSizeMax = 2.0f;

// �ړ����x
static constexpr int kMoveSpeed = 4;
static constexpr int kMoveSpeedPowerup = 1;
static constexpr int kMoveSpeedMax = 6;

// ���ˊԊu
static constexpr int kShotInterval = 16;
static constexpr int kShotIntervalPowerup = -2;
static constexpr int kShotIntervalMin = 8;

// ���x���ɉ������V���b�g�f�[�^
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
// �V���b�g�̍ő僌�x��
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
}

void Player::update()
{
	if (!m_isExist)	return;
	
	// �Q�[���N���A��̉��o
	if (m_seq == Seq::kSeqGameClear)
	{
		m_pos.x += getPlayerSpeed() * 2;
		return;
	}

	// ���G����
	m_damageFrame--;
	if (m_damageFrame < -1)	m_damageFrame = -1;

	// �ړ�
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

	m_vec.z = 0.0f;
	if(isInput)
	{
		VectorNormalize(&m_vec, &m_vec);
	}

	VectorScale(&m_vec, &m_vec, static_cast<float>(getPlayerSpeed()));

	m_pos.x += m_vec.x;
	m_pos.y += m_vec.y;

	if (m_pos.x < 0.0f + m_radius)		m_pos.x = (0.0f + m_radius);
	if (m_pos.x > Game::cScreenWidth - m_radius)	m_pos.x = (Game::cScreenWidth - m_radius);
	if (m_pos.y < 0.0f + m_radius)		m_pos.y = (0.0f + m_radius);
	if (m_pos.y > Game::cScreenHeight - m_radius)	m_pos.y = (Game::cScreenHeight - m_radius);

	// �V���b�g
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
			// �e�̏����ݒ���s��
			if (pShot)
			{
				pShot->setMoveSpeed(m_shotData[i].speed);
				pShot->setMoveAngle(m_shotData[i].angle);

				pShot->setPower(getShotDamage());
				pShot->setScale(getShotScale());
			}
		}
#else
		// �O���V���b�g
		int frontNum = m_powerUp[kPowerupTypeShotDir]+1;
		if (frontNum > 5)	frontNum = 5;
		int startAngle = -(frontNum-1) * 5;
		for (int i = 0; i < frontNum; i++)
		{
			Shot* pShot = nullptr;
			pShot = m_pMain->createPlayerShot(getPos());
			// �e�̏����ݒ���s��
			if (pShot)
			{
				pShot->setMoveSpeed(kShotSpeed);
				pShot->setMoveAngle(startAngle + i*10);
				pShot->setPower(getShotDamage());
				pShot->setScale(getShotScale());
			}
		}

		// ����V���b�g
		int backNum = m_powerUp[kPowerupTypeBackShot];
		if (backNum > 3)	backNum = 3;
		startAngle = -(backNum - 1) * 5;
		for (int i = 0; i < backNum; i++)
		{
			Shot* pShot = nullptr;
			pShot = m_pMain->createPlayerShot(getPos());
			// �e�̏����ݒ���s��
			if (pShot)
			{
				pShot->setMoveSpeed(kShotSpeed);
				pShot->setMoveAngle(180 + startAngle + i * 10);
				pShot->setPower(getShotDamage());
				pShot->setScale(getShotScale());
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
		GameObject::draw();
	}
	

	// HP�Q�[�W�̕\��
	if (m_maxHp <= 0)	return;

	int x1 = static_cast<int>(m_pos.x - kHpBarLen / 2);
	int x2 = static_cast<int>(m_pos.x + kHpBarLen / 2);
	int y1 = static_cast<int>(m_pos.y + 32);
	int y2 = y1 + kHpBarHeight;
	DrawBox(x1, y1, x2, y2, GetColor(0, 255, 0), false);
	x2 = x1 + kHpBarLen * m_hp / m_maxHp;
	DrawBox(x1, y1, x2, y2, GetColor(0, 255, 0), true);

	// ���x���A�o���l�\��
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
	// ���G���Ԓ��̓_���[�W�󂯂Ȃ�
	if (m_damageFrame >= 0)	return false;
	// �Q�[���N���A��Ȃǂ̓_���[�W�󂯂Ȃ�
	if( m_seq != Seq::kSeqMain )	return false;

	return true;
}

void Player::damage(int getDamage)
{
	// ���G���Ԓ��̓_���[�W�󂯂Ȃ�
	if (m_damageFrame >= 0)	return;

	int dealt = getDamage;
	dealt -= m_damagePrevent;
	if (dealt < 1)	dealt = 1;

	int last = m_hp;
	m_hp -= dealt;
	m_damageFrame = kDamageFrame;

	// ���S������
	if(last > 0 && m_hp <= 0)
	{
		Sound::PlaySound(Sound::kSoundID_Dead);
	}
}

// �p���[�A�b�v�֘A����
void Player::addExp(int add)
{
	m_exp += add;

	// ���x���オ������p���[�A�b�v
	if (m_exp >= getNextLevelExp())
	{
		m_exp -= getNextLevelExp();
		m_level++;

		setShot(m_level);
		Sound::PlaySound(Sound::kSoundID_Levelup);

		// test
		int levelUpType = GetRand(kPowerupTypeNum - 1);
		m_powerUp[levelUpType]++;
//		for (int i = 0; i < kPowerupTypeNum; i++)
//		{
//			m_powerUp[i]++;
//		}

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
	result += kShotSizePowerup * m_powerUp[kPowerupTypeShotPower];	// �U���͂ŃT�C�Y���ς��
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
