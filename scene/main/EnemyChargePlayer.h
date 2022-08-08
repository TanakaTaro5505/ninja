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

	// ¶¬‚É‰Šú‰»	createGraphic‚Ì‚ ‚Æ
	void init(int maxHp) override;
	void update() override;
//	void draw() override;

private:

};