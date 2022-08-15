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

	// �������ɏ�����	createGraphic�̂���
	void init(int maxHp) override;
	void update() override;
//	void draw() override;

private:

	// ���݈ʒu����v���C���[�ʒu�ւ̃x�N�g�����擾
	Vec2 getToPlayer();

	// �i�ފp�x
	float m_dir;
};