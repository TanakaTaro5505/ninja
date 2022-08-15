#pragma once
#include "GameObject.h"
#include "EnemyBase.h"

class EnemyChargePlayer : public EnemyBase
{
public:
	EnemyChargePlayer() : EnemyBase()
	{
		m_dir = 0.0f;
	}
	virtual ~EnemyChargePlayer() {}

	// 生成時に初期化	createGraphicのあと
	void init(int maxHp) override;
	void update() override;
//	void draw() override;

private:

	// 現在位置からプレイヤー位置へのベクトルを取得
	Vec2 getToPlayer();

	// 進む角度
	float m_dir;
};