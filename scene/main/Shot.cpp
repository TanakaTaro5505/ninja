#include "Shot.h"
#include "Game.h"
#include <math.h>

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