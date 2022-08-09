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
	m_dir = atan2f(playerPos.y - getPos().y, playerPos.x - getPos().x);

//	toPlayer = VNorm(toPlayer);
//	m_vec = VScale(toPlayer, kSpeed);

	m_vec.x = cosf(m_dir) * kSpeed;
	m_vec.y = sinf(m_dir) * kSpeed;
	m_vec.z = 0.0f;

	m_angle = m_dir + 3.1459f;	// 進行方向に向ける
}

void EnemyChargePlayer::update()
{
	if (!m_isExist)	return;

	m_pos.x += m_vec.x;
	m_pos.y += m_vec.y;

#if 0	// 外積を使用してなす角を求める
//	VECTOR VCross(VECTOR In1, VECTOR In2);

#endif

#if 1	// 行列変換を使用してなす角を求める
	// 0度の方向を向くベクトル
	constexpr VECTOR kBase = {1,0,0};
	//現在の進行方向を0度の方向に変換する行列を取得
	MATRIX mtx = MGetRotVec2(m_vec, kBase);

	VECTOR toPlayer = getToPlayer();

	// プレイヤー方向へのベクトルを変換する
	VECTOR tempVec = VTransform(toPlayer, mtx);

	float diffDir = atan2f(tempVec.y, tempVec.x);
	if( abs(diffDir) < 3.141592f/2 )	// 90度以上で追いかけるのをあきらめる
	{
		if (diffDir > 0.0f)
		{
			m_dir += 0.01f;
		}
		else if (diffDir < 0.0f)
		{
			m_dir -= 0.01f;
		}
	}

	m_vec.x = cosf(m_dir) * kSpeed;
	m_vec.y = sinf(m_dir) * kSpeed;
	m_vec.z = 0.0f;

	m_angle = m_dir + 3.1459f;	// 進行方向に向ける
#endif

	if (m_pos.x < 0.0f - m_radius)
	{
		m_isExist = false;
	}
}

VECTOR EnemyChargePlayer::getToPlayer()
{
	VECTOR playerPos = m_pMain->getPlayer()->getPos();
	VECTOR toPlayer;
	toPlayer.x = playerPos.x - m_pos.x;
	toPlayer.y = playerPos.y - m_pos.y;
	toPlayer.z = 0.0f;

	return toPlayer;
}