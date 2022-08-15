#include "EnemyChargePlayer.h"
#include "Game.h"
#include "Sound.h"
#include <math.h>

#include "Shot.h"
#include "SceneMain.h"

// 進行速度
static constexpr float kSpeed = 8.0f;
// 旋回性能
static constexpr float kRotSpeed = 0.005f;

// ===================================================================================
void EnemyChargePlayer::init(int maxHp)
{
	EnemyBase::init(maxHp);

	// 初期位置からプレイヤーに向かって移動するようにする
	Vec2 playerPos = m_pMain->getPlayer()->getPos();
	m_dir = atan2f(playerPos.y - getPos().y, playerPos.x - getPos().x);

//	toPlayer = VNorm(toPlayer);
//	m_vec = VScale(toPlayer, kSpeed);

	m_vec.x = cosf(m_dir) * kSpeed;
	m_vec.y = sinf(m_dir) * kSpeed;

	m_angle = m_dir + 3.1459f;	// 進行方向に向ける
}

void EnemyChargePlayer::update()
{
	if (!m_isExist)	return;

	m_pos.x += m_vec.x;
	m_pos.y += m_vec.y;

#if 0	// 外積を使用してなす角を求める
	VECTOR toPlayer = getToPlayer();
	VECTOR tempVec = VCross(m_vec, toPlayer);
	if (tempVec.z > 0.0f)
	{
		m_dir += kRotSpeed;
	}
	else if (tempVec.z < 0.0f)
	{
		m_dir -= kRotSpeed;
	}

#endif

#if 1	// 行列変換を使用してなす角を求める
	// 0度の方向を向くベクトル
	constexpr VECTOR kBase = {1,0,0};
	VECTOR tempVec;
	tempVec.x = m_vec.x;
	tempVec.y = m_vec.y;
	tempVec.z = 0.0f;
	//現在の進行方向を0度の方向に変換する行列を取得
	MATRIX mtx = MGetRotVec2(tempVec, kBase);

	VECTOR toPlayer;
	toPlayer.x = getToPlayer().x;
	toPlayer.y = getToPlayer().y;
	toPlayer.z = 0.0f;

	// プレイヤー方向へのベクトルを変換する
	VECTOR calcVec = VTransform(toPlayer, mtx);

	float diffDir = atan2f(calcVec.y, calcVec.x);
	if( abs(diffDir) < 3.141592f/2 )	// 90度以上で追いかけるのをあきらめる
	{
		if (diffDir > 0.0f)
		{
			m_dir += kRotSpeed;
		}
		else if (diffDir < 0.0f)
		{
			m_dir -= kRotSpeed;
		}
	}
#endif

	// m_dirから進行方向と画像の回転情報を作成
	m_vec.x = cosf(m_dir) * kSpeed;
	m_vec.y = sinf(m_dir) * kSpeed;

	m_angle = m_dir + 3.1459f;	// 進行方向に向ける

	if (m_pos.x < 0.0f - m_radius)
	{
		m_isExist = false;
	}
}

Vec2 EnemyChargePlayer::getToPlayer()
{
	Vec2 playerPos = m_pMain->getPlayer()->getPos();
	Vec2 toPlayer;
	toPlayer.x = playerPos.x - m_pos.x;
	toPlayer.y = playerPos.y - m_pos.y;

	return toPlayer;
}