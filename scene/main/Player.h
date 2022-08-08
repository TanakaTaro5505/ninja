#pragma once
#include "GameObject.h"

class SceneMain;

class Player : public GameObject
{
public:
	enum class Seq
	{
		kSeqMain,		// ���i�̃Q�[����
		kSeqGameOver,	// �Q�[���I�[�o�[���o
		kSeqGameClear,	// �Q�[���N���A���o
		
		kSeqNum
	};
	typedef struct ShotData
	{
		// ���ˊJ�n�ʒu	�v���C���[�ʒu����̍���
		float startOffsetX;
		float startOffsetY;
		// ���x
		float speed;
		// �p�x
		float angle;
		// �U����
		int power;
	}ShotData;
public:
	Player() : GameObject()
	{
		m_pMain = nullptr;

		m_seq = Seq::kSeqMain;

		m_hp = 0;
		m_maxHp = 0;
		m_shotSpeed = 0;
		m_shotInterval = 0;
		m_moveSpeed = 0;
		m_damagePrevent = 0;

		m_lastShot = 0;
		m_damageFrame = -1;

		m_level = 0;
		m_exp = 0;

		m_shotNum = 0;
	}
	virtual ~Player() {}

	void init();
	void update();
	void draw();

	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	// �Q�[���N���A���ɃV�[�P���X�ύX
	void setSeq(Seq seq) { m_seq = seq; }

	// �_���[�W���󂯂邩
	bool isGetDamage();
	// �_���[�W���󂯂鏈��
	void damage( int getDamage );

	int getHp() { return m_hp; }
	int getShotSpeed() { return m_shotSpeed; }
	int getShotInterval() { return m_shotInterval; }

	// �p���[�A�b�v�֘A
	void addExp(int add);	// �o���l���Z
	int getLevel();			// ���݂̃��x���擾
	int getNextLevelExp();	// ���̃��x���ɂȂ�̂ɕK�v�Ȍo���l
private:
	// define----------------------------
	static constexpr int kShotMax = 32;	// 1��̔��˂ŏo��V���b�g�̍ő吔

	// function----------------------------
	// �V���b�g�f�[�^�ݒ�
	void setShot( int level );
private:
	// variable----------------------------
	SceneMain* m_pMain;
	Seq m_seq;

	// �L�����N�^�[���\
	int m_hp;
	int m_maxHp;
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
	int m_shotNum;
	ShotData m_shotData[kShotMax];
};
