#include "EnemyBase.h"
#include "Game.h"
#include "Sound.h"
#include <math.h>

#include "SceneMain.h"
#include "Player.h"

// HPバー表示
static const int kHpBarLen		= 80;
static const int kHpBarHeight	= 8;

// ===================================================================================
void EnemyBase::init(int maxHp)
{
	m_maxHp = maxHp;
	m_hp = m_maxHp;
}

void EnemyBase::update()
{
	if (!m_isExist)	return;

	m_pos.x += m_vec.x;
	m_pos.y += m_vec.y;

	if (m_pos.x < 0.0f - m_radius)
	{
		m_isExist = false;
	}
}

void EnemyBase::draw()
{
	if (!m_isExist)	return;
	GameObject::draw();

	// HPゲージの表示
	if (m_maxHp <= 0)	return;
	int x1 = static_cast<int>(m_pos.x - kHpBarLen / 2);
	int x2 = static_cast<int>(m_pos.x + kHpBarLen / 2);
	int y1 = static_cast<int>(m_pos.y + 32);
	int y2 = y1 + kHpBarHeight;
	DrawBox(x1, y1, x2, y2, GetColor(255,0,0), false);
	x2 = x1 + kHpBarLen * m_hp / m_maxHp;
	DrawBox(x1, y1, x2, y2, GetColor(255, 0, 0), true);
}

void EnemyBase::hit(int damage)
{
	Sound::PlaySound(Sound::kSoundID_Hit);

	m_hp -= damage;
	if(m_hp <= 0)
	{
		m_isExist = false;
	}
}

void EnemyBase::erase()
{
	m_isExist = false;
}