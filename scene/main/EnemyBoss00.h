#pragma once
#include "GameObject.h"
#include "EnemyBase.h"

class EnemyBoss00 : public EnemyBase
{
public:
	EnemyBoss00() : EnemyBase()
	{
		m_basePos = { 0.0f, 0.0f };
		m_sinRate = 0.0f;
		m_shotWait = 0;
		m_summonWait = 0;

		m_pUpdateFunc = nullptr;
	}
	virtual ~EnemyBoss00() {}

	// �������ɏ�����	createGraphic�̂���
	void init(int maxHp) override;
	void update() override;
//	void draw() override;
	void dead() override;

	bool isBoss() override { return true; }

private:
	// �V�[�P���X���Ƃ̏���
	void updateAppear();
	void updateMain();
private:

	Vec2 m_basePos;
	float m_sinRate;
	int m_shotWait;		// �e�̔��ˊԊu

	int m_summonWait;	// �G���G�����Ԋu

	void (EnemyBoss00::* m_pUpdateFunc)();
};