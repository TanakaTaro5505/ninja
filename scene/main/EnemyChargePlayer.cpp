#include "EnemyChargePlayer.h"
#include "Game.h"
#include "Sound.h"
#include <math.h>

#include "Shot.h"
#include "SceneMain.h"

// �i�s���x
static constexpr float kSpeed = 8.0f;
// ���񐫔\
static constexpr float kRotSpeed = 0.005f;

// ===================================================================================
void EnemyChargePlayer::init(int maxHp)
{
	EnemyBase::init(maxHp);

	// �����ʒu����v���C���[�Ɍ������Ĉړ�����悤�ɂ���
	Vec2 playerPos = m_pMain->getPlayer()->getPos();
	m_dir = atan2f(playerPos.y - getPos().y, playerPos.x - getPos().x);

//	toPlayer = VNorm(toPlayer);
//	m_vec = VScale(toPlayer, kSpeed);

	m_vec.x = cosf(m_dir) * kSpeed;
	m_vec.y = sinf(m_dir) * kSpeed;

	m_angle = m_dir + 3.1459f;	// �i�s�����Ɍ�����
}

void EnemyChargePlayer::update()
{
	if (!m_isExist)	return;

	m_pos.x += m_vec.x;
	m_pos.y += m_vec.y;

#if 0	// �O�ς��g�p���ĂȂ��p�����߂�
	VECTOR toPlayer = getToPlayer();
	VECTOR tempVec = VCross(m_vec, toPlayer);
	if (tempVec.z > 0.0f)
	{
		m_dir += kRotSpeed;
	}
	else if (tempVec.z < 0.0f)
	{
		m_dir -= kRotSpeed;
	}

#endif

#if 1	// �s��ϊ����g�p���ĂȂ��p�����߂�
	// 0�x�̕����������x�N�g��
	constexpr VECTOR kBase = {1,0,0};
	VECTOR tempVec;
	tempVec.x = m_vec.x;
	tempVec.y = m_vec.y;
	tempVec.z = 0.0f;
	//���݂̐i�s������0�x�̕����ɕϊ�����s����擾
	MATRIX mtx = MGetRotVec2(tempVec, kBase);

	VECTOR toPlayer;
	toPlayer.x = getToPlayer().x;
	toPlayer.y = getToPlayer().y;
	toPlayer.z = 0.0f;

	// �v���C���[�����ւ̃x�N�g����ϊ�����
	VECTOR calcVec = VTransform(toPlayer, mtx);

	float diffDir = atan2f(calcVec.y, calcVec.x);
	if( abs(diffDir) < 3.141592f/2 )	// 90�x�ȏ�Œǂ�������̂�������߂�
	{
		if (diffDir > 0.0f)
		{
			m_dir += kRotSpeed;
		}
		else if (diffDir < 0.0f)
		{
			m_dir -= kRotSpeed;
		}
	}
#endif

	// m_dir����i�s�����Ɖ摜�̉�]�����쐬
	m_vec.x = cosf(m_dir) * kSpeed;
	m_vec.y = sinf(m_dir) * kSpeed;

	m_angle = m_dir + 3.1459f;	// �i�s�����Ɍ�����

	if (m_pos.x < 0.0f - m_radius)
	{
		m_isExist = false;
	}
}

Vec2 EnemyChargePlayer::getToPlayer()
{
	Vec2 playerPos = m_pMain->getPlayer()->getPos();
	Vec2 toPlayer;
	toPlayer.x = playerPos.x - m_pos.x;
	toPlayer.y = playerPos.y - m_pos.y;

	return toPlayer;
}