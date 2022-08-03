#include "Item.h"
#include "Game.h"
#include <math.h>

static constexpr float kItemSpeed = 2.0f;

// ===================================================================================
void Item::update()
{
	if (!m_isExist)	return;

	m_pos.x -= kItemSpeed;
	if (m_pos.x < 0.0f - 32.0f)
	{
		m_isExist = false;
	}
}
#if false
void Item::draw()
{
	if (!m_isExist)	return;

	DrawCircleAA(m_pos.x, m_pos.y, m_radius, 16, GetColor(0,0,255));
	DrawString(m_pos.x - 8, m_pos.y - 8, "ƒA", GetColor(255, 255, 255));
}
#endif
void Item::erase()
{
	m_isExist = false;
}