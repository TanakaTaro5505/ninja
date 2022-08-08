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

	// 生成時に初期化	createGraphicのあと
	virtual void init(int maxHp);
	virtual void update() = 0;
	virtual void draw();
	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	virtual bool isBoss() { return false; }

	// 敵にショットをあてた	与えるダメージを指定する
	void hit(int damage);
	// 強制終了
	void erase();

	// ぶつかったときのダメージ
	int getHitDamage() { return m_hitDamage; }
	void setHitDamage(int damage) { m_hitDamage = damage; }
	// ショットにぶつかったときのダメージ
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