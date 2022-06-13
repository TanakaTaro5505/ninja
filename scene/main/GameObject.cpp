#include "GameObject.h"

// ===================================================================================
GameObject::GameObject()
{
	m_isExist = false;
	m_graphicHandle = -1;

	m_color = GetColor(255, 255, 255);
	m_radius = 0.0f;

	m_pos.x = 0.0f;
	m_pos.y = 0.0f;

	m_vec.x = 0.0f;
	m_vec.y = 0.0f;

	m_graphicSizeX = 0;
	m_graphicSizeY = 0;
}

void GameObject::create(float x, float y, float radius, unsigned int color)
{
	m_isExist = true;
	m_graphicHandle = -1;

	m_pos.x = x;
	m_pos.y = y;

	m_vec.x = 0.0f;
	m_vec.y = 0.0f;

	m_graphicSizeX = 0;
	m_graphicSizeY = 0;

	m_radius = radius;
	m_color = color;
}

void GameObject::createGraphic(float x, float y, int handle)
{
	m_isExist = true;
	m_graphicHandle = handle;

	m_pos.x = x;
	m_pos.y = y;

	m_vec.x = 0.0f;
	m_vec.y = 0.0f;

	GetGraphSize(handle, &m_graphicSizeX, &m_graphicSizeY);

	m_radius = static_cast<float>(m_graphicSizeX/2);
}

void GameObject::update()
{
	if (!m_isExist)	return;

	m_pos.x += m_vec.x;
	m_pos.y += m_vec.y;

	if (m_pos.x < 0.0f + m_radius)		m_pos.x = (0.0f + m_radius);
	if (m_pos.x > 800.0f - m_radius)	m_pos.x = (800.0f - m_radius);
	if (m_pos.y < 0.0f + m_radius)		m_pos.y = (0.0f + m_radius);
	if (m_pos.y > 600.0f - m_radius)	m_pos.y = (600.0f - m_radius);

}

void GameObject::draw()
{
	if (!m_isExist)	return;

	if (m_graphicHandle >= 0)
	{
		DrawGraph(static_cast<int>(m_pos.x)- m_graphicSizeX/2, static_cast<int>(m_pos.y) - m_graphicSizeY/2, m_graphicHandle, true);
	}
	else
	{
		DrawCircleAA(m_pos.x, m_pos.y, m_radius, 16, m_color);
	}
}

bool GameObject::isCol(GameObject* target)
{
	// 存在しないオブジェクトとは衝突しない
	if (!m_isExist)	return false;
	if (!target->isExist())	return false;

	float colDist = m_radius + target->getRadius();

	VECTOR targetVec;
	targetVec.x = target->getPos().x - m_pos.x;
	targetVec.y = target->getPos().y - m_pos.y;

	float sqDist = targetVec.x * targetVec.x + targetVec.y * targetVec.y;
	if (sqDist < colDist * colDist)
	{
		return true;
	}
	return false;
}

