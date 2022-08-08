#pragma once
#include "GameObject.h"
#include "EnemyBase.h"

class EnemyBoss00 : public EnemyBase
{
public:
	EnemyBoss00() : EnemyBase()
	{
		m_basePos = { 0.0f, 0.0f,0.0f };
		m_sinRate = 0.0f;
		m_shotWait = 0;
	}
	virtual ~EnemyBoss00() {}

	// �������ɏ�����	createGraphic�̂���
	void init(int maxHp) override;
	void update() override;
//	void draw() override;

	bool isBoss() override { return true; }

private:

	VECTOR m_basePos;
	float m_sinRate;
	int m_shotWait;
};