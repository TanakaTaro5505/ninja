#include "Shot.h"
#include "Game.h"
#include <math.h>

#include "SceneMain.h"

static constexpr float cShotSpeed = 8.0f;
static constexpr float cRotSpeed = 0.2f;

// ===================================================================================
void Shot::update()
{
	if (!m_isExist)	return;

	float rad = 3.141592f * m_moveAngle / 180.0f;
	m_vec.x = cosf(rad) * m_moveSpeed;
	m_vec.y = sinf(rad) * m_moveSpeed;

	m_pos.x += m_vec.x;
	m_pos.y += m_vec.y;
#if false	// test
	if (m_isPlayerShot)
	{
		VECTOR targetEnemyPos;
		if (m_pMain->getNearEnemyPos(&targetEnemyPos, m_pos))
		{
#if false	
			// test	完全追尾
			m_moveAngle = atan2f(targetEnemyPos.y - m_pos.y, targetEnemyPos.x - m_pos.x);
			m_moveAngle = m_moveAngle * 180.0f / 3.141592f;
#else
			// 0度の方向を向くベクトル
			constexpr VECTOR kBase = { 1,0,0 };
			//現在の進行方向を0度の方向に変換する行列を取得
			MATRIX mtx = MGetRotVec2(m_vec, kBase);

			VECTOR toEnemy;
			toEnemy.x = targetEnemyPos.x - m_pos.x;
			toEnemy.y = targetEnemyPos.y - m_pos.y;
			toEnemy.z = 0.0f;

			// プレイヤー方向へのベクトルを変換する
			VECTOR tempVec = VTransform(toEnemy, mtx);

			float diffDir = atan2f(tempVec.y, tempVec.x);
			if (diffDir > 0.0f)
			{
				m_moveAngle += 1.0f;
			}
			else if (diffDir < 0.0f)
			{
				m_moveAngle -= 1.0f;
			}
#endif
		}
	}
#endif
	addAngle(m_rotVec);

	if (m_pos.x < 0.0f - m_radius)					m_isExist = false;
	if (m_pos.x > Game::cScreenWidth + m_radius)	m_isExist = false;
	if (m_pos.y < 0.0f - m_radius)					m_isExist = false;
	if (m_pos.y > Game::cScreenHeight + m_radius)	m_isExist = false;
}
void Shot::createPlayerShot(VECTOR pos, int graph)
{
	createGraphic(pos.x, pos.y, graph);

	m_moveSpeed = cShotSpeed;
	m_moveAngle = 0.0f;

	m_rotVec = cRotSpeed;

	m_isPlayerShot = true;
}

void Shot::createEnemyShot(VECTOR pos, int graph)
{
	createGraphic(pos.x, pos.y, graph);

	m_moveSpeed = cShotSpeed;
	m_moveAngle = 180.0f;

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