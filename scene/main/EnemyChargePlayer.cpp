#include "EnemyChargePlayer.h"
#include "Game.h"
#include "Sound.h"
#include <math.h>

#include "Shot.h"
#include "SceneMain.h"

static constexpr float kSpeed = 8.0f;

// ===================================================================================
void EnemyChargePlayer::init(int maxHp)
{
	EnemyBase::init(maxHp);

	// 初期位置からプレイヤーに向かって移動するようにする
	VECTOR playerPos = m_pMain->getPlayer()->getPos();
	VECTOR toPlayer;
	toPlayer.x = playerPos.x - m_pos.x;
	toPlayer.y = playerPos.y - m_pos.y;
	toPlayer.z = 0.0f;
	float playerDir = atan2f(playerPos.y - getPos().y, playerPos.x - getPos().x);
	toPlayer = VNorm(toPlayer);
	m_vec = VScale(toPlayer, kSpeed);
	m_angle = playerDir + 3.1459f;	// 進行方向に向ける
}

void EnemyChargePlayer::update()
{
	if (!m_isExist)	return;

	m_pos.x += m_vec.x;
	m_pos.y += m_vec.y;

	if (m_pos.x < 0.0f - m_radius)
	{
		m_isExist = false;
	}
}
