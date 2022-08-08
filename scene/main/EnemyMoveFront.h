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

	// ¶¬‚É‰Šú‰»	createGraphic‚Ì‚ ‚Æ
	void init(int maxHp);
	void update();
private:

	int m_shotWait;
};