#include "EnemyMoveFront.h"
#include "Game.h"
#include "Sound.h"
#include <math.h>

#include "Shot.h"
#include "SceneMain.h"

static constexpr float kSpeed = -4.0f;

// ===================================================================================
void EnemyMoveFront::init(int maxHp)
{
	EnemyBase::init(maxHp);

	m_vec.x = -kSpeed;
	m_vec.y = 0.0f;
	m_vec.z = 0.0f;
	m_shotWait = 120;
}

void EnemyMoveFront::update()
{
	if (!m_isExist)	return;

	EnemyBase::update();

	m_shotWait--;

	if (m_shotWait == 0)
	{
		Shot* pShot = nullptr;
		pShot = m_pMain->createEnemyShot(getPos());
		// ’e‚Ì‰ŠúÝ’è‚ðs‚¤
		if (pShot)
		{
			pShot->setMoveSpeed(8);
			pShot->setMoveAngle(180);
			pShot->setPower(getShotDamage());
		}
	}
}