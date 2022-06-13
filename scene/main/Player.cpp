#include "Player.h"
#include "Game.h"

static const int kHpBarLen = 80;
static const int kHpBarHeight = 8;

static const int kExpBarLen = 80;
static const int kExpBarHeight = 8;
// �_���[�W�󂯂���̖��G����(�t���[��)
static const int kDamageFrame = 60;

// ��{���\
static const int kMaxHp			= 100;
static const int kShotDamage	= 10;
static const int kShotSpeed		= 6;
static const int kShotInterval	= 8;
static const int kMoveSpeed		= 4;
static const int kDamagePrevent = 0;

// ===================================================================================
void Player::init()
{
	m_maxHp = kMaxHp;
	m_hp = m_maxHp;
	m_shotPower = kShotDamage;
	m_shotSpeed = kShotSpeed;
	m_shotInterval = kShotInterval;
	m_moveSpeed = kMoveSpeed;
	m_damagePrevent = kDamagePrevent;

	m_level = 0;
	m_exp = 0;
}

void Player::update()
{
	if (!m_isExist)	return;

	m_damageFrame--;
	if (m_damageFrame < -1)	m_damageFrame = -1;

	bool isInput = false;
	if (Pad::isPress(PAD_INPUT_LEFT))
	{
		m_vec.x = -1.0f;
		isInput = true;
	}
	else if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		m_vec.x = 1.0f;
		isInput = true;
	}
	else
	{
		m_vec.x = 0.0f;
	}

	if (Pad::isPress(PAD_INPUT_UP))
	{
		m_vec.y = -1.0f;
		isInput = true;
	}
	else if (Pad::isPress(PAD_INPUT_DOWN))
	{
		m_vec.y = 1.0f;
		isInput = true;
	}
	else
	{
		m_vec.y = 0.0f;
	}

	m_vec.z = 0.0f;
	if(isInput)
	{
		VectorNormalize(&m_vec, &m_vec);
	}

	VectorScale(&m_vec, &m_vec, m_moveSpeed);

	m_pos.x += m_vec.x;
	m_pos.y += m_vec.y;

	if (m_pos.x < 0.0f + m_radius)		m_pos.x = (0.0f + m_radius);
	if (m_pos.x > Game::cScreenWidth - m_radius)	m_pos.x = (Game::cScreenWidth - m_radius);
	if (m_pos.y < 0.0f + m_radius)		m_pos.y = (0.0f + m_radius);
	if (m_pos.y > Game::cScreenHeight - m_radius)	m_pos.y = (Game::cScreenHeight - m_radius);
}

void Player::draw()
{
	if (!m_isExist)	return;
	if( (m_damageFrame < 0) || (m_damageFrame % 2) )
	{
		GameObject::draw();
	}
	

	// HP�Q�[�W�̕\��
	if (m_maxHp <= 0)	return;

	int x1 = m_pos.x - kHpBarLen / 2;
	int x2 = m_pos.x + kHpBarLen / 2;
	int y1 = m_pos.y + 32;
	int y2 = y1 + kHpBarHeight;
	DrawBox(x1, y1, x2, y2, GetColor(0, 255, 0), false);
	x2 = x1 + kHpBarLen * m_hp / m_maxHp;
	DrawBox(x1, y1, x2, y2, GetColor(0, 255, 0), true);

	// ���x���A�o���l�\��
	x1 = m_pos.x - kExpBarLen / 2;
	x2 = m_pos.x + kExpBarLen / 2;
	y1 = m_pos.y - 32;
	y2 = y1 + kExpBarHeight;
	DrawBox(x1, y1, x2, y2, GetColor(255, 255, 0), false);
	x2 = x1 + kExpBarLen * m_exp / getNextLevelExp();
	DrawBox(x1, y1, x2, y2, GetColor(255, 255, 0), true);

	DrawFormatString(m_pos.x - kHpBarLen / 2-8, m_pos.y - 32, GetColor(255, 255, 255), "%d", getLevel());
}

void Player::damage(int getDamage)
{
	// ���G���Ԓ��̓_���[�W�󂯂Ȃ�
	if (m_damageFrame >= 0)	return;

	int dealt = getDamage;
	dealt -= m_damagePrevent;
	if (dealt < 1)	dealt = 1;

	m_hp -= dealt;
	m_damageFrame = kDamageFrame;
}

// �p���[�A�b�v�֘A����
void Player::addExp(int add)
{
	m_exp += add;

	// ���x���オ������p���[�A�b�v
	if (m_exp >= getNextLevelExp())
	{
		m_exp -= getNextLevelExp();
		m_level++;
	}
}

int Player::getLevel()
{
	return m_level;
}

int Player::getNextLevelExp()
{
	return 15 + getLevel() * 5;
}
