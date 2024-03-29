#pragma once
#include "GameObject.h"

class SceneMain;

class Shot : public GameObject
{
public:
	Shot() : GameObject() 
	{
		m_pMain = nullptr;
		m_frameCount = 0;

		m_rotVec = 0.0f;
		m_moveSpeed = 0.0f;
		m_moveAngle = 0.0f;
		m_power = 0;
		m_homingFrame = -1;
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
	void createPlayerShot(Vec2 pos, int graph );
	// 敵のショット作成
	void createEnemyShot(Vec2 pos, int graph );

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
	// 敵を追いかけるフレーム数設定	-1だと追いかけない
	void setHoming(int frame = kDefaultHomingFrame) { m_homingFrame = frame; }

	// プレイヤーに当たる弾
	bool isHitPlayer(void) { return !m_isPlayerShot; }
	// 敵に当たる弾
	bool isHitEnemy(void) { return m_isPlayerShot; }
private:
	// 残像表示フレーム数
	static constexpr int kPosLogNum = 16;
	// ホーミング弾追尾フレーム数デフォルト
	static constexpr int kDefaultHomingFrame = 60;
private:
	SceneMain* m_pMain;
	int	m_frameCount;

	float m_rotVec;
	float m_moveSpeed;	// 進行方向
	float m_moveAngle;	// deg

	int m_power;	// 攻撃力

	int m_homingFrame;	// 対象を追いかけるフレーム数	-1だともともと追いかけない

	int m_isPlayerShot;	// プレイヤーの撃った弾か	そうでないならプレイヤーに当たる

	Vec2 m_posLog[kPosLogNum];
	float m_angleLog[kPosLogNum];
};
