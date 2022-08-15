#include "EnemyMoveFrontSin.h"
#include "Game.h"
#include "Sound.h"
#include <math.h>

#include "Shot.h"
#include "SceneMain.h"

static constexpr float kSpeed = -4.0f;

// ===================================================================================
void EnemyMoveFrontSin::init(int maxHp)
{
	EnemyBase::init(maxHp);

	m_vec.x = kSpeed;
	m_vec.y = 0.0f;
	m_shotWait = 120;

	m_basePos = m_pos;
	m_sinRate = 0.0f;
}

void EnemyMoveFrontSin::update()
{
	if (!m_isExist)	return;

	m_sinRate += 0.05f;

	m_basePos.x += kSpeed;

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
		// ’e‚Ì‰ŠúÝ’è‚ðs‚¤
		if (pShot)
		{
			pShot->setMoveSpeed(8);
			pShot->setPower(getShotDamage());
			// ƒvƒŒƒCƒ„[‚Ì•û‚É’e‚ðŒ‚‚Â
			Player* pPlayer = m_pMain->getPlayer();
			float dir = atan2f(pPlayer->getPos().y - getPos().y, pPlayer->getPos().x - getPos().x);
			float dirRad = dir / 3.1459f * 180.0f;
			pShot->setMoveAngle(dirRad);
		}
	}
}
