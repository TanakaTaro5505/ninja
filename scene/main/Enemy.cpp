#include "Enemy.h"
#include "Game.h"
#include "Sound.h"
#include <math.h>

#include "SceneMain.h"

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

void Enemy::Hit(int damage)
{
	Sound::PlaySound(Sound::kSoundID_Hit);

	m_hp -= damage;
	if(m_hp <= 0)
	{
		m_isExist = false;
	}
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
	m_sinRate += 0.1f;

	m_basePos.x -= 4.0f;

	m_pos.x = m_basePos.x;
	m_pos.y = m_basePos.y + sinf(m_sinRate) * 80.0f;

	if (m_pos.x < 0.0f - m_radius)
	{
		m_isExist = false;
	}
}