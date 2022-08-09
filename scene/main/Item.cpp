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

void Item::draw()
{
	if (!m_isExist)	return;

	GameObject::draw();

	// アイテム演出
#if false
	for (int i = 0; i <64; i++)
	{
		int posX = m_pos.x + GetRand(32) - 16;
		int posY = m_pos.y + GetRand(32) - 16;
	//	DrawPixel(posX, posY, GetColor(255, 0, 0));
		DrawCircleAA(posX, posY, 1.0f, 8, GetColor(255, 0, 0));
	}
#endif
}

void Item::erase()
{
	m_isExist = false;
}