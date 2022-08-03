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

void Item::erase()
{
	m_isExist = false;
}