#include "EnemyBoss00.h"
#include "Game.h"
#include "Sound.h"
#include <math.h>

#include "Shot.h"
#include "SceneMain.h"

#include "EnemyMoveFront.h"
namespace
{
	static constexpr float kSpeed = -4.0f;
	static constexpr float kBasePosX = 880.0f;

	// 1âÒÇÃÉVÉáÉbÉgÇ≈ÇÃíeê∂ê¨êî
	static constexpr int kShotNum = 5;
	// íeÇÃë¨ìx
	static constexpr int kShotSpeed = 8;
	// ÉVÉáÉbÉgÇÃî≠éÀä‘äu
	static constexpr int kShotInterval = 30;
	// éGãõìGÇÃê∂ê¨ä‘äu
	static constexpr int kSummonInterval = 120;

}

// ===================================================================================
void EnemyBoss00::init(int maxHp)
{
	EnemyBase::init(maxHp);

	m_hpBarLen = 120;

	m_basePos = m_pos;

	m_vec.x = kSpeed;
	m_vec.y = 0.0f;
	m_shotWait = 120;
	m_summonWait = 180;

	m_sinRate = 0.0f;
	m_scale = 2.0f;

	m_pUpdateFunc = &EnemyBoss00::updateAppear;
}

void EnemyBoss00::update()
{
	if (!m_isExist)	return;

	(this->*m_pUpdateFunc)();
}

void EnemyBoss00::dead()
{
	Sound::PlaySound(Sound::kSoundID_BossDead);

	// îöî≠ââèo
	for (int i = 0; i < 8; i++)
	{
		Vec2 pos = getPos();
		pos.x += static_cast<float>(GetRand(64) - 32);
		pos.y += static_cast<float>(GetRand(64) - 32);
		m_pMain->createDeadEffect(pos);
	}

	// ÉAÉCÉeÉÄÇÕê∂éYÇµÇ»Ç¢
}

void EnemyBoss00::updateAppear()
{
	m_basePos.x -= 4.0f;
	m_pos.x = m_basePos.x;
	m_pos.y = m_basePos.y;

	if (m_basePos.x < kBasePosX)
	{
		m_basePos.x = kBasePosX;
		m_pUpdateFunc = &EnemyBoss00::updateMain;
	}
}

void EnemyBoss00::updateMain()
{
	m_sinRate += 0.02f;
	m_pos.x = m_basePos.x;
	m_pos.y = m_basePos.y + sinf(m_sinRate) * 240.0f;

	m_shotWait--;
	if (m_shotWait == 0)
	{
		Sound::PlaySound(Sound::kSoundID_BossAttack);

		for (int i = 0; i < kShotNum; i++)
		{
			Shot* pShot = nullptr;
			pShot = m_pMain->createEnemyShot(getPos());
			// íeÇÃèâä˙ê›íËÇçsÇ§
			if (pShot)
			{
				pShot->setMoveSpeed(kShotSpeed);
				pShot->setMoveAngle(static_cast<float>(180 - 40 + i * 20));
				pShot->setPower(getShotDamage());
				// É{ÉXÇÕÇ≈Ç©Ç¢íeÇåÇÇ¬
				pShot->setScale(4.0f);
			}
		}

		m_shotWait = kShotInterval;
	}
	m_summonWait--;
	if (m_summonWait == 0)
	{
		EnemyBase* pEnemy = new EnemyMoveFront;

		VECTOR pos;
		pos.x = Game::cScreenWidth + 64.0f;
		pos.y = static_cast<float>(GetRand(Game::cScreenHeight - 160) + 80);
		pos.z = 0.0f;

		pEnemy->createGraphic(pos.x, pos.y, m_pMain->getEnemyGraphic());
		pEnemy->setMain(m_pMain);

		pEnemy->init(20);
		pEnemy->setHitDamage(10);
		pEnemy->setShotDamage(10);
		m_pMain->addEnemy(pEnemy);

		m_summonWait = kSummonInterval;
	}
}