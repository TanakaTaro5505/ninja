#pragma once
#include "GameObject.h"
#include "EnemyBase.h"

class EnemyMoveFront : public EnemyBase
{
public:

public:
	EnemyMoveFront() : EnemyBase()
	{
		m_shotWait = 0;
	}
	virtual ~EnemyMoveFront() {}

	// 生成時に初期化	createGraphicのあと
	void init(int maxHp);
	void update();
private:

	int m_shotWait;
};