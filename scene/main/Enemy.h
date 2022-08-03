#pragma once
#include "GameObject.h"

class SceneMain;

class Enemy : public GameObject
{
public:
	enum class Type
	{
		kTypeCharge,	// �O�i����̂�
		kTypeChargeSin,	// �T�C���J�[�u�`���O�i

		kTypeBoss00,	// �X�e�[�W1�{�X

		kTypeNum
	};

public:
	Enemy() : GameObject() 
	{
		m_pMain = nullptr;

		m_type = Type::kTypeCharge;

		m_hp = 0;
		m_maxHp = 0;

		m_hitDamage = 0;
		m_shotDamage = 0;
		m_shotWait = 0;

		m_basePos = {0.0f, 0.0f,0.0f};
		m_sinRate = 0.0f;
	}
	virtual ~Enemy() {}

	// �������ɏ�����	createGraphic�̂���
	void init(int maxHp, Type type);
	void update();
	void draw();
	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	// �G�ɃV���b�g�����Ă�	�^����_���[�W���w�肷��
	void hit(int damage);
	// �����I��
	void erase();

	bool isBoss();

	int getHitDamage() { return m_hitDamage; }
	void setHitDamage(int damage) { m_hitDamage = damage; }
	int getShotDamage() { return m_shotDamage; }
	void setShotDamage(int damage) { m_shotDamage = damage; }

	int getShotWait() { return m_shotWait; }
	void setShotWait(int wait) { m_shotWait = wait; }

private:
	// �G�̃^�C�v�ʍX�V����
	void updateCharge();
	void updateChargeSin();
	void updateBoss00();

	SceneMain* m_pMain;

	Type	m_type;

	int m_hp;
	int m_maxHp;

	int m_hitDamage;
	int m_shotDamage;

	// �e�����܂ł̎���	0��菬�����ꍇ�͌����Ȃ�
	int m_shotWait;

	// ����Ȉړ����s���ꍇ�p
	VECTOR m_basePos;
	float m_sinRate;
};