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

	// 生成時に初期化	createGraphicのあと
	void init(int maxHp);
	void update();
	void draw();
	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	// 敵にショットをあてた	与えるダメージを指定する
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

	// 弾を撃つまでの時間	0より小さい場合は撃たない
	int m_shotWait;
};