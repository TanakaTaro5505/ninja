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

		m_hitDamage = 0;
		m_shotDamage = 0;
	}
	virtual ~EnemyBase() {}

	// �������ɏ�����	createGraphic�̂���
	void init(int maxHp);
	void update();
	void draw();
	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	// �G�ɃV���b�g�����Ă�	�^����_���[�W���w�肷��
	void hit(int damage);
	// �����I��
	void erase();

	bool isBoss() { return false; }

	// �Ԃ������Ƃ��̃_���[�W
	int getHitDamage() { return m_hitDamage; }
	void setHitDamage(int damage) { m_hitDamage = damage; }
	// �V���b�g�ɂԂ������Ƃ��̃_���[�W
	int getShotDamage() { return m_shotDamage; }
	void setShotDamage(int damage) { m_shotDamage = damage; }

private:

	SceneMain* m_pMain;

	int m_hp;
	int m_maxHp;

	int m_hitDamage;
	int m_shotDamage;
};