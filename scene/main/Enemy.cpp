#include "Enemy.h"
#include "Game.h"

static const int kHpBarLen		= 80;
static const int kHpBarHeight	= 8;

// ===================================================================================
void Enemy::init(int maxHp)
{
	m_maxHp = maxHp;
	m_hp = m_maxHp;
}

void Enemy::update()
{
	if (!m_isExist)	return;

	m_vec.x = -4.0f;

	m_pos.x += m_vec.x;
	m_pos.y += m_vec.y;

	if (m_pos.x < 0.0f - m_radius)
	{
		m_isExist = false;
	}

	m_shotWait--;
}

void Enemy::draw()
{
	if (!m_isExist)	return;
	GameObject::draw();

	// HPƒQ[ƒW‚Ì•\Ž¦
	if (m_maxHp <= 0)	return;
	int x1= m_pos.x - kHpBarLen / 2;
	int x2 = m_pos.x + kHpBarLen / 2;
	int y1 = m_pos.y + 32;
	int y2 = y1 + kHpBarHeight;
	DrawBox(x1, y1, x2, y2, GetColor(255,0,0), false);
	x2 = x1 + kHpBarLen * m_hp / m_maxHp;
	DrawBox(x1, y1, x2, y2, GetColor(255, 0, 0), true);
}

void Enemy::Hit(int damage)
{
	m_hp -= damage;
	if(m_hp <= 0)
	{
		m_isExist = false;
	}
}