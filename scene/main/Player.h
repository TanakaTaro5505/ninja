#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player() : GameObject() 
	{
		m_hp = 0;
		m_maxHp = 0;
		m_shotPower = 0;
		m_shotSpeed = 0;
		m_shotInterval = 0;
		m_moveSpeed = 0;
		m_damagePrevent = 0;

		m_damageFrame = -1;

		m_level = 0;
		m_exp = 0;
	}
	virtual ~Player() {}

	void init();
	void update();
	void draw();

	void damage( int getDamage );

	int getHp() { return m_hp; }
	int getShotPower() { return m_shotPower; }
	int getShotSpeed() { return m_shotSpeed; }
	int getShotInterval() { return m_shotInterval; }

	// パワーアップ関連
	void addExp(int add);	// 経験値加算
	int getLevel();			// 現在のレベル取得
	int getNextLevelExp();	// 次のレベルになるのに必要な経験値
private:
	// キャラクター性能
	int m_hp;
	int m_maxHp;
	int m_shotPower;	// ショットの攻撃力
	int m_shotSpeed;	// ショットの速度
	int m_shotInterval;	// 連射速度(待ち時間)
	int m_moveSpeed;	// 移動速度
	int m_damagePrevent;// 防御力

	// ダメージ受けた後の無敵時間
	int m_damageFrame;

	// レベルアップ
	int m_level;
	int m_exp;
};
