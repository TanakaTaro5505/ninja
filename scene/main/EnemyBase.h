#pragma once
#include "GameObject.h"

class SceneMain;

class EnemyBase : public GameObject
{
public:

public:
	EnemyBase() : GameObject()
	{
		m_pMain = nullptr;

		m_hp = 0;
		m_maxHp = 0;
		m_hpBarLen = 0;

		m_hitDamage = 0;
		m_shotDamage = 0;
	}
	virtual ~EnemyBase() {}

	// �������ɏ�����	createGraphic�̂���
	virtual void init(int maxHp);
	virtual void update() = 0;
	virtual void draw();
	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	virtual bool isBoss() { return false; }

	// �G�ɃV���b�g�����Ă�	�^����_���[�W���w�肷��
	void hit(int damage);
	// �����I��
	void erase();

	// �Ԃ������Ƃ��̃_���[�W
	int getHitDamage() { return m_hitDamage; }
	void setHitDamage(int damage) { m_hitDamage = damage; }
	// �V���b�g�ɂԂ������Ƃ��̃_���[�W
	int getShotDamage() { return m_shotDamage; }
	void setShotDamage(int damage) { m_shotDamage = damage; }

protected:

	SceneMain* m_pMain;

	int m_hp;
	int m_maxHp;
	int m_hpBarLen;

	int m_hitDamage;
	int m_shotDamage;
};