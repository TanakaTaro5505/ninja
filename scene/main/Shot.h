#pragma once
#include "GameObject.h"

class SceneMain;

class Shot : public GameObject
{
public:
	Shot() : GameObject() 
	{
		m_pMain = nullptr;

		m_rotVec = 0.0f;
		m_moveSpeed = 0.0f;
		m_moveAngle = 0.0f;
		m_power = 0;
		m_isPlayerShot = false;
		for( int i = 0; i < kPosLogNum; i++)
		{
			m_posLog[i] = m_pos;
			m_angleLog[i] = m_angle;
		}
	}
	virtual ~Shot() {}

	void setMain(SceneMain* pMain) { m_pMain = pMain; }
	void update();
	void draw();

	// プレイヤーのショット作成
	void createPlayerShot( VECTOR pos, int graph );
	// 敵のショット作成
	void createEnemyShot( VECTOR pos, int graph );

	// ショットをあてた
	void hit();
	// 強制終了
	void erase();
	// 移動情報設定
	void setMoveSpeed(float speed) { m_moveSpeed = speed; }
	void setMoveAngle(float angle) { m_moveAngle = angle; }

	// 攻撃力
	void setPower(int power) { m_power = power; }
	int getPower() { return m_power; }

	// プレイヤーに当たる弾
	bool isHitPlayer(void) { return !m_isPlayerShot; }
	// 敵に当たる弾
	bool isHitEnemy(void) { return m_isPlayerShot; }
private:
	static constexpr int kPosLogNum = 16;
private:
	SceneMain* m_pMain;
	float m_rotVec;

	float m_moveSpeed;
	float m_moveAngle;	// deg

	int m_power;	// 攻撃力

	int m_isPlayerShot;	// プレイヤーの撃った弾か	そうでないならプレイヤーに当たる

	VECTOR m_posLog[kPosLogNum];
	float m_angleLog[kPosLogNum];
};
