#pragma once
#include "GameObject.h"
#include "EnemyBase.h"

class EnemyMoveFrontSin : public EnemyBase
{
public:
	EnemyMoveFrontSin() : EnemyBase()
	{
		m_basePos = { 0.0f, 0.0f };
		m_sinRate = 0.0f;
		m_shotWait = 0;
	}
	virtual ~EnemyMoveFrontSin() {}

	// ¶¬‚É‰Šú‰»	createGraphic‚Ì‚ ‚Æ
	void init(int maxHp) override;
	void update() override;
//	void draw() override;

private:

	Vec2 m_basePos;
	float m_sinRate;
	int m_shotWait;
};