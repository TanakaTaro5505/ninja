#pragma once
#include "GameObject.h"

class SceneMain;

class Enemy : public GameObject
{
public:
	Enemy() : GameObject() 
	{
		m_pMain = nullptr;
		m_hp = 0;
		m_maxHp = 0;

		m_hitDamage = 0;
		m_shotDamage = 0;
		m_shotWait = 0;
	}
	virtual ~Enemy() {}

	// �������ɏ�����	createGraphic�̂���
	void init(int maxHp);
	void update();
	void draw();
	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	// �G�ɃV���b�g�����Ă�	�^����_���[�W���w�肷��
	void Hit(int damage);

	int getHitDamage() { return m_hitDamage; }
	void setHitDamage(int damage) { m_hitDamage = damage; }
	int getShotDamage() { return m_shotDamage; }
	void setShotDamage(int damage) { m_shotDamage = damage; }

	int getShotWait() { return m_shotWait; }
	void setShotWait(int wait) { m_shotWait = wait; }
private:

	SceneMain* m_pMain;

	int m_hp;
	int m_maxHp;

	int m_hitDamage;
	int m_shotDamage;

	// �e�����܂ł̎���	0��菬�����ꍇ�͌����Ȃ�
	int m_shotWait;
};