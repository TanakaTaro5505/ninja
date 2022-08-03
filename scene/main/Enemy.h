#pragma once
#include "GameObject.h"

class SceneMain;

class Enemy : public GameObject
{
public:
	enum class Type
	{
		kTypeCharge,	// 前進するのみ
		kTypeChargeSin,	// サインカーブ描く前進

		kTypeBoss00,	// ステージ1ボス

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

	// 生成時に初期化	createGraphicのあと
	void init(int maxHp, Type type);
	void update();
	void draw();
	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	// 敵にショットをあてた	与えるダメージを指定する
	void hit(int damage);
	// 強制終了
	void erase();

	bool isBoss();

	int getHitDamage() { return m_hitDamage; }
	void setHitDamage(int damage) { m_hitDamage = damage; }
	int getShotDamage() { return m_shotDamage; }
	void setShotDamage(int damage) { m_shotDamage = damage; }

	int getShotWait() { return m_shotWait; }
	void setShotWait(int wait) { m_shotWait = wait; }

private:
	// 敵のタイプ別更新処理
	void updateCharge();
	void updateChargeSin();
	void updateBoss00();

	SceneMain* m_pMain;

	Type	m_type;

	int m_hp;
	int m_maxHp;

	int m_hitDamage;
	int m_shotDamage;

	// 弾を撃つまでの時間	0より小さい場合は撃たない
	int m_shotWait;

	// 特殊な移動を行う場合用
	VECTOR m_basePos;
	float m_sinRate;
};