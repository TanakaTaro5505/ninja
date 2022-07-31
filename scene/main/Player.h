#pragma once
#include "GameObject.h"

class SceneMain;

class Player : public GameObject
{
public:
	Player() : GameObject() 
	{
		m_pMain = nullptr;

		m_hp = 0;
		m_maxHp = 0;
		m_shotPower = 0;
		m_shotSpeed = 0;
		m_shotInterval = 0;
		m_moveSpeed = 0;
		m_damagePrevent = 0;

		m_lastShot = 0;
		m_damageFrame = -1;

		m_level = 0;
		m_exp = 0;
	}
	virtual ~Player() {}

	void init();
	void update();
	void draw();

	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	void damage( int getDamage );

	int getHp() { return m_hp; }
	int getShotPower() { return m_shotPower; }
	int getShotSpeed() { return m_shotSpeed; }
	int getShotInterval() { return m_shotInterval; }

	// �p���[�A�b�v�֘A
	void addExp(int add);	// �o���l���Z
	int getLevel();			// ���݂̃��x���擾
	int getNextLevelExp();	// ���̃��x���ɂȂ�̂ɕK�v�Ȍo���l
private:

	SceneMain* m_pMain;

	// �L�����N�^�[���\
	int m_hp;
	int m_maxHp;
	int m_shotPower;	// �V���b�g�̍U����
	int m_shotSpeed;	// �V���b�g�̑��x
	int m_shotInterval;	// �A�ˑ��x(�҂�����)
	int m_moveSpeed;	// �ړ����x
	int m_damagePrevent;// �h���

	// �v���C���
	// �V���b�g�������Ă���̌o�߃t���[����
	int m_lastShot;
	// �_���[�W�󂯂���̖��G����
	int m_damageFrame;

	// ���x���A�b�v
	int m_level;
	int m_exp;

	// �V���b�g���
	
};
