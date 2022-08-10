#include "EnemyBoss00.h"
#include "Game.h"
#include "Sound.h"
#include <math.h>

#include "Shot.h"
#include "SceneMain.h"

static constexpr float kSpeed = -4.0f;

// ===================================================================================
void EnemyBoss00::init(int maxHp)
{
	EnemyBase::init(maxHp);

	m_hpBarLen = 120;

	m_basePos = m_pos;

	m_vec.x = kSpeed;
	m_vec.y = 0.0f;
	m_vec.z = 0.0f;
	m_shotWait = 120;

	m_sinRate = 0.0f;
	m_scale = 2.0f;
}

void EnemyBoss00::update()
{
	if (!m_isExist)	return;

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
				pShot->setMoveAngle(static_cast<float>(180 - 40 + i * 20));
				pShot->setPower(getShotDamage());
				// ボスはでかい弾を撃つ
				pShot->setScale(4.0f);
			}
		}

		m_shotWait = 30;
	}
}

void EnemyBoss00::dead()
{
	
	for (int i = 0; i < 8; i++)
	{
		VECTOR pos = getPos();
		pos.x += static_cast<float>(GetRand(64) - 32);
		pos.y += static_cast<float>(GetRand(64) - 32);
		m_pMain->createDeadEffect(pos);
	}

	// アイテムは生産しない
}