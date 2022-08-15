#include "Shot.h"
#include "Game.h"
#include <math.h>

#include "SceneMain.h"

static constexpr float cShotSpeed = 8.0f;
static constexpr float cRotSpeed = 0.2f;
// ホーミング弾旋回性能
static constexpr float cHomingRotSpeed = 4.0f;

// ===================================================================================
void Shot::update()
{
	if (!m_isExist)	return;

	m_frameCount++;

	float rad = 3.141592f * m_moveAngle / 180.0f;
	m_vec.x = cosf(rad) * m_moveSpeed;
	m_vec.y = sinf(rad) * m_moveSpeed;

	for (int i = kPosLogNum - 1; i >= 1; i--)
	{
		m_posLog[i] = m_posLog[i - 1];
		m_angleLog[i] = m_angleLog[i - 1];
	}
	m_posLog[0] = m_pos;
	m_angleLog[0] = m_angle;

	m_pos.x += m_vec.x;
	m_pos.y += m_vec.y;
	addAngle(m_rotVec);

	if ((m_homingFrame >= 0) && (m_homingFrame > m_frameCount))
	{
		Vec2 targetEnemyPos;

		if (m_isPlayerShot)
		{
			if (m_pMain->getNearEnemyPos(&targetEnemyPos, m_pos))
			{
				// 0度の方向を向くベクトル
				constexpr VECTOR kBase = { 1,0,0 };
				VECTOR tempVec;
				tempVec.x = m_vec.x;
				tempVec.y = m_vec.y;
				tempVec.z = 0.0f;
				//現在の進行方向を0度の方向に変換する行列を取得
				MATRIX mtx = MGetRotVec2(tempVec, kBase);

				VECTOR toEnemy;
				toEnemy.x = targetEnemyPos.x - m_pos.x;
				toEnemy.y = targetEnemyPos.y - m_pos.y;
				toEnemy.z = 0.0f;

				// プレイヤー方向へのベクトルを変換する
				VECTOR calcVec = VTransform(toEnemy, mtx);

				float diffDir = atan2f(calcVec.y, calcVec.x);
				if (diffDir > 0.0f)
				{
					m_moveAngle += cHomingRotSpeed;
				}
				else if (diffDir < 0.0f)
				{
					m_moveAngle -= cHomingRotSpeed;
				}
			}
			else
			{
				// 敵を見失ったらホーミングやめる
				m_homingFrame = -1;
			}
		}
	}
	else
	{
		if (m_pos.x < 0.0f - m_radius)					m_isExist = false;
		if (m_pos.x > Game::cScreenWidth + m_radius)	m_isExist = false;
		if (m_pos.y < 0.0f - m_radius)					m_isExist = false;
		if (m_pos.y > Game::cScreenHeight + m_radius)	m_isExist = false;
	}
}

void Shot::draw()
{
	if (!m_isExist)	return;

	//	const int kAlphaIntervel = 256 / kPosLogNum;
	const int kAlphaIntervel = 128 / kPosLogNum;
	for (int i = kPosLogNum - 1; i >= 0; i--)
	{
		int alpha = kAlphaIntervel * ((kPosLogNum - 1) - i);
		if (alpha >= 255)	alpha = 255;
		if (alpha < 0)		alpha = 0;

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawRotaGraph2(static_cast<int>(m_posLog[i].x), static_cast<int>(m_posLog[i].y),
			m_graphicSizeX / 2, m_graphicSizeY / 2,
			m_scale, 0.0,		// m_angle, m_aangleLog[i]	などあるが回さないのがよさげ？
			m_graphicHandle, true, false);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	GameObject::draw();
}

void Shot::createPlayerShot(Vec2 pos, int graph)
{
	createGraphic(pos.x, pos.y, graph);
	m_frameCount = 0;

	for (int i = 0; i < kPosLogNum; i++)
	{
		m_posLog[i] = m_pos;
	}
	m_moveSpeed = cShotSpeed;
	m_moveAngle = 0.0f;
	m_homingFrame = -1;

	m_rotVec = cRotSpeed;

	m_isPlayerShot = true;
}

void Shot::createEnemyShot(Vec2 pos, int graph)
{
	createGraphic(pos.x, pos.y, graph);
	m_frameCount = 0;

	for (int i = 0; i < kPosLogNum; i++)
	{
		m_posLog[i] = m_pos;
	}
	m_moveSpeed = cShotSpeed;
	m_moveAngle = 180.0f;
	m_homingFrame = -1;

	m_rotVec = -cRotSpeed;

	m_isPlayerShot = false;
}

void Shot::hit()
{
	m_isExist = false;
}

void Shot::erase()
{
	m_isExist = false;
}