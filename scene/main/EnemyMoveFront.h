#pragma once
#include "GameObject.h"
#include "EnemyBase.h"

class EnemyMoveFront : public EnemyBase
{
public:
	EnemyMoveFront() : EnemyBase()
	{
		m_shotWait = 0;
	}
	virtual ~EnemyMoveFront() {}

	// 生成時に初期化	createGraphicのあと
	void init(int maxHp) override;
	void update() override;
//	void draw() override;

private:

	int m_shotWait;
};