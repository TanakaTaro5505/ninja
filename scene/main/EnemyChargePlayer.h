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

	// �������ɏ�����	createGraphic�̂���
	void init(int maxHp) override;
	void update() override;
//	void draw() override;

private:

};