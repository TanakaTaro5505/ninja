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

	// 生成時に初期化	createGraphicのあと
	void init(int maxHp);
	void update();
	void draw();
	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	// 敵にショットをあてた	与えるダメージを指定する
	void hit(int damage);
	// 強制終了
	void erase();

	bool isBoss() { return false; }

	// ぶつかったときのダメージ
	int getHitDamage() { return m_hitDamage; }
	void setHitDamage(int damage) { m_hitDamage = damage; }
	// ショットにぶつかったときのダメージ
	int getShotDamage() { return m_shotDamage; }
	void setShotDamage(int damage) { m_shotDamage = damage; }

private:

	SceneMain* m_pMain;

	int m_hp;
	int m_maxHp;

	int m_hitDamage;
	int m_shotDamage;
};