#pragma once
#include "GameObject.h"

class Shot : public GameObject
{
public:
	Shot() : GameObject() 
	{
		m_angle = 0.0f;
		m_rotVec = 0.0f;
		m_moveSpeed = 0.0f;
		m_moveAngle = 0.0f;
		m_power = 0;
		m_isPlayerShot = false;
	}
	virtual ~Shot() {}

	void update();
	void draw();

	// �v���C���[�̃V���b�g�쐬
	void createPlayerShot( VECTOR pos, int graph );
	// �G�̃V���b�g�쐬
	void createEnemyShot( VECTOR pos, int graph );

	// �V���b�g�����Ă�
	void Hit();
	// �ړ����ݒ�
	void setMoveSpeed(float speed) { m_moveSpeed = speed; }
	void setMoveAngle(float angle) { m_moveAngle = angle; }

	// �U����
	void setPower(int power) { m_power = power; }
	int getPower() { return m_power; }

	// �v���C���[�ɓ�����e
	bool isHitPlayer(void) { return !m_isPlayerShot; }
	// �G�ɓ�����e
	bool isHitEnemy(void) { return m_isPlayerShot; }
private:
	float m_angle;	// �ʂ̉�](���o)
	float m_rotVec;

	float m_moveSpeed;
	float m_moveAngle;	// deg

	int m_power;	// �U����

	int m_isPlayerShot;	// �v���C���[�̌������e��	�����łȂ��Ȃ�v���C���[�ɓ�����
};
