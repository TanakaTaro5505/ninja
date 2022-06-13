#include "EffectManager.h"
#include <math.h>

// ===================================================================
EffectManager::Particle::Particle()
{
	m_existFrame = -1;
	m_color = GetColor(255, 255, 255);
	m_pos = {0.0f, 0.0f};
	m_vec = {0.0f, 0.0f};
}

bool EffectManager::Particle::create(float x, float y)
{
	if (m_existFrame >= 0)	return false;

	m_existFrame = GetRand(40) + 20;
	m_pos.x = x;
	m_pos.y = y;
	
	float speed = GetRand(30) + 15;
	int angle = GetRand(360);
	float deg = (3.141592f * 2.0f / 360.0f) * angle;

	m_vec.x = cosf(deg) * speed/10.0f;
	m_vec.y = sinf(deg) * speed/10.0f;
	return true;
}

void EffectManager::Particle::update()
{
	if (m_existFrame < 0)	return;
	m_existFrame--;
	m_pos.x += m_vec.x;
	m_pos.y += m_vec.y;

	m_vec.y += 0.2f;
}

void EffectManager::Particle::draw()
{
	if (m_existFrame < 0)	return;
//	DrawPixel(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), GetColor(255, 255, 255));
	int x1 = static_cast<int>(m_pos.x) - 1;
	int x2 = x1 + 2;
	int y1 = static_cast<int>(m_pos.y) - 1;
	int y2 = y1 + 2;
	DrawBox(x1, y1, x2, y2, GetColor(255, 255, 255), true);
}

// ===================================================================
EffectManager::EffectManager()
{
}
EffectManager::~EffectManager()
{
}

void EffectManager::create(float x, float y)
{
	int particleNum = 64;
	for (int i = 0; i < cParticleMax; i++)
	{
		if( m_particle[i].create(x, y) )	particleNum--;
		if (particleNum <= 0)	break;
	}
}
void EffectManager::update()
{
	for (int i = 0; i < cParticleMax; i++)
	{
		m_particle[i].update();
	}
}

void EffectManager::draw()
{
	for (int i = 0; i < cParticleMax; i++)
	{
		m_particle[i].draw();
	}
}