#pragma once
#include "GameObject.h"
#include "EnemyBase.h"

class EnemyBoss00 : public EnemyBase
{
public:
	EnemyBoss00() : EnemyBase()
	{
		m_basePos = { 0.0f, 0.0f };
		m_sinRate = 0.0f;
		m_shotWait = 0;
		m_summonWait = 0;

		m_pUpdateFunc = nullptr;
	}
	virtual ~EnemyBoss00() {}

	// 生成時に初期化	createGraphicのあと
	void init(int maxHp) override;
	void update() override;
//	void draw() override;
	void dead() override;

	bool isBoss() override { return true; }

private:
	// シーケンスごとの処理
	void updateAppear();
	void updateMain();
private:

	Vec2 m_basePos;
	float m_sinRate;
	int m_shotWait;		// 弾の発射間隔

	int m_summonWait;	// 雑魚敵生成間隔

	void (EnemyBoss00::* m_pUpdateFunc)();
};