#pragma once
#include "GameObject.h"
#include "EnemyBase.h"

class EnemyChargePlayer : public EnemyBase
{
public:
	EnemyChargePlayer() : EnemyBase()
	{
	}
	virtual ~EnemyChargePlayer() {}

	// 生成時に初期化	createGraphicのあと
	void init(int maxHp) override;
	void update() override;
//	void draw() override;

private:

};