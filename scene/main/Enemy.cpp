#include "Enemy.h"
#include "Game.h"
#include "Sound.h"
#include <math.h>

#include "SceneMain.h"
#include "Player.h"

// HPバー表示
static const int kHpBarLen		= 80;
static const int kHpBarHeight	= 8;

// ===================================================================================
void Enemy::init(int maxHp, Type type)
{
	m_maxHp = maxHp;
	m_hp = m_maxHp;

	// タイプ別の初期化
	m_type = type;
	m_basePos = m_pos;
	m_sinRate = 0.0f;

	VECTOR playerPos = m_pMain->getPlayer()->getPos();
	VECTOR toPlayer;
	toPlayer.x = playerPos.x - m_pos.x;
	toPlayer.y = playerPos.y - m_pos.y;
	toPlayer.z = 0.0f;
	float playerDir = atan2f(playerPos.y - getPos().y, playerPos.x - getPos().x);
	switch (m_type)
	{
	case Enemy::Type::kTypeChargePlayer:
		toPlayer = VNorm(toPlayer);
		m_vec = VScale(toPlayer, 6.0f);
		m_angle = playerDir + 3.1459f;	// 進行方向に向ける
		break;
	case Enemy::Type::kTypeBoss00:
		m_scale = 2.0f;
		break;
	}
}

void Enemy::update()
{
	if (!m_isExist)	return;

	switch (m_type)
	{
	case Enemy::Type::kTypeCharge:
		updateCharge();
		break;
	case Enemy::Type::kTypeChargeSin:
		updateChargeSin();
		break;
	case Enemy::Type::kTypeChargePlayer:
		updateChargePlayer();
		break;
	case Enemy::Type::kTypeBoss00:
		updateBoss00();
		break;
	case Enemy::Type::kTypeNum:
	default:
		// assert
		break;
	}
}

void Enemy::draw()
{
	if (!m_isExist)	return;
	GameObject::draw();

	// HPゲージの表示
	if (m_maxHp <= 0)	return;
	int x1 = static_cast<int>(m_pos.x - kHpBarLen / 2);
	int x2 = static_cast<int>(m_pos.x + kHpBarLen / 2);
	int y1 = static_cast<int>(m_pos.y + 32);
	int y2 = y1 + kHpBarHeight;
	DrawBox(x1, y1, x2, y2, GetColor(255,0,0), false);
	x2 = x1 + kHpBarLen * m_hp / m_maxHp;
	DrawBox(x1, y1, x2, y2, GetColor(255, 0, 0), true);
}

void Enemy::hit(int damage)
{
	Sound::PlaySound(Sound::kSoundID_Hit);

	m_hp -= damage;
	if(m_hp <= 0)
	{
		m_isExist = false;
	}
}

void Enemy::erase()
{
	m_isExist = false;
}

bool Enemy::isBoss()
{
	switch (m_type)
	{
	case Type::kTypeBoss00:
		return true;
	}
	return false;
}

void Enemy::updateCharge()
{
	m_vec.x = -4.0f;

	m_pos.x += m_vec.x;
	m_pos.y += m_vec.y;

	if (m_pos.x < 0.0f - m_radius)
	{
		m_isExist = false;
	}

	m_shotWait--;
	if (m_shotWait == 0)
	{
		Shot* pShot = nullptr;
		pShot = m_pMain->createEnemyShot(getPos());
		// 弾の初期設定を行う
		if (pShot)
		{
			pShot->setMoveSpeed(8);
			pShot->setMoveAngle(180);
			pShot->setPower(getShotDamage());
		}
	}
}

void Enemy::updateChargeSin()
{
	m_sinRate += 0.05f;

	m_basePos.x -= 4.0f;

	m_pos.x = m_basePos.x;
	m_pos.y = m_basePos.y + sinf(m_sinRate) * 80.0f;

	if (m_pos.x < 0.0f - m_radius)
	{
		m_isExist = false;
	}


	m_shotWait--;
	if (m_shotWait == 0)
	{
		Shot* pShot = nullptr;
		pShot = m_pMain->createEnemyShot(getPos());
		// 弾の初期設定を行う
		if (pShot)
		{
			pShot->setMoveSpeed(8);
			pShot->setPower(getShotDamage());
			// プレイヤーの方に弾を撃つ
			Player* pPlayer = m_pMain->getPlayer();
			float dir = atan2f(pPlayer->getPos().y - getPos().y, pPlayer->getPos().x - getPos().x);
			float dirRad = dir / 3.1459f * 180.0f;
			pShot->setMoveAngle(dirRad);
		}
	}
}

void Enemy::updateChargePlayer()
{
	m_pos.x += m_vec.x;
	m_pos.y += m_vec.y;

	if (m_pos.x < 0.0f - m_radius)
	{
		m_isExist = false;
	}
}

void Enemy::updateBoss00()
{
	bool isStartLoop = true;
	if (m_basePos.x > 900.0f)
	{
		m_basePos.x -= 4.0f;
		if (m_basePos.x <= 900.0f)
		{
			m_basePos.x = 900.0f;
		}
		else
		{
			isStartLoop = false;
		}
	}
	// 定位置についた後
	if (isStartLoop)
	{
		m_sinRate += 0.02f;
	}

	m_pos.x = m_basePos.x;
	m_pos.y = m_basePos.y + sinf(m_sinRate) * 240.0f;

	m_shotWait--;
	if (m_shotWait == 0)
	{
		for (int i = 0; i < 5; i++)
		{
			Shot* pShot = nullptr;
			pShot = m_pMain->createEnemyShot(getPos());
			// 弾の初期設定を行う
			if (pShot)
			{
				pShot->setMoveSpeed(8);
				pShot->setMoveAngle(180 - 40 + i * 20);
				pShot->setPower(getShotDamage());
				// ボスはでかい弾を撃つ
				pShot->setScale(4.0f);
			}
		}

		m_shotWait = 30;
	}
}