#include "EnemyChargePlayer.h"
#include "Game.h"
#include "Sound.h"
#include <math.h>

#include "Shot.h"
#include "SceneMain.h"

static constexpr float kSpeed = 8.0f;

// ===================================================================================
void EnemyChargePlayer::init(int maxHp)
{
	EnemyBase::init(maxHp);

	// �����ʒu����v���C���[�Ɍ������Ĉړ�����悤�ɂ���
	VECTOR playerPos = m_pMain->getPlayer()->getPos();
	m_dir = atan2f(playerPos.y - getPos().y, playerPos.x - getPos().x);

//	toPlayer = VNorm(toPlayer);
//	m_vec = VScale(toPlayer, kSpeed);

	m_vec.x = cosf(m_dir) * kSpeed;
	m_vec.y = sinf(m_dir) * kSpeed;
	m_vec.z = 0.0f;

	m_angle = m_dir + 3.1459f;	// �i�s�����Ɍ�����
}

void EnemyChargePlayer::update()
{
	if (!m_isExist)	return;

	m_pos.x += m_vec.x;
	m_pos.y += m_vec.y;

#if 0	// �O�ς��g�p���ĂȂ��p�����߂�
//	VECTOR VCross(VECTOR In1, VECTOR In2);

#endif

#if 1	// �s��ϊ����g�p���ĂȂ��p�����߂�
	// 0�x�̕����������x�N�g��
	constexpr VECTOR kBase = {1,0,0};
	//���݂̐i�s������0�x�̕����ɕϊ�����s����擾
	MATRIX mtx = MGetRotVec2(m_vec, kBase);

	VECTOR toPlayer = getToPlayer();

	// �v���C���[�����ւ̃x�N�g����ϊ�����
	VECTOR tempVec = VTransform(toPlayer, mtx);

	float diffDir = atan2f(tempVec.y, tempVec.x);
	if( abs(diffDir) < 3.141592f/2 )	// 90�x�ȏ�Œǂ�������̂�������߂�
	{
		if (diffDir > 0.0f)
		{
			m_dir += 0.01f;
		}
		else if (diffDir < 0.0f)
		{
			m_dir -= 0.01f;
		}
	}

	m_vec.x = cosf(m_dir) * kSpeed;
	m_vec.y = sinf(m_dir) * kSpeed;
	m_vec.z = 0.0f;

	m_angle = m_dir + 3.1459f;	// �i�s�����Ɍ�����
#endif

	if (m_pos.x < 0.0f - m_radius)
	{
		m_isExist = false;
	}
}

VECTOR EnemyChargePlayer::getToPlayer()
{
	VECTOR playerPos = m_pMain->getPlayer()->getPos();
	VECTOR toPlayer;
	toPlayer.x = playerPos.x - m_pos.x;
	toPlayer.y = playerPos.y - m_pos.y;
	toPlayer.z = 0.0f;

	return toPlayer;
}