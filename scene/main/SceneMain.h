#pragma once
#include "DxLib.h"
#include "SceneManager.h"
#include "PadUtil.h"

#include "Command.h"
#include "Player.h"
#include "Shot.h"
#include "Enemy.h"
#include "StageManager.h"

#include "Effect/EffectManager.h"

class SceneMain : public SceneBase
{
	//define ----------------------------------
private:
	static constexpr int cShotMax = 128;
	static constexpr int cEnemyMax = 64;

	static constexpr int cStarNum = 64;

	enum class Seq
	{
		kSeqMain,
		kSeqStageClear,
		kSeqGameover,

		kSeNum
	};

	//function ----------------------------------
public:
	SceneMain() : SceneBase()
	{
		m_seq = Seq::kSeqMain;
		m_endWait = -1;
		m_fadeBright = 0;

		m_playerGraphic = 0;
		m_shotGraphic = 0;
		m_enemyShotGraphic = 0;
		m_enemyGraphic = 0;
	}
	virtual ~SceneMain()
	{
	}

	void init();
	void deleteGraph();
	SceneBase* update();
	void draw();

	// �G����
	void createEnemy(VECTOR pos, int hp, Enemy::Type type);

	// �v���C���[�擾
	Player* getPlayer() { return &m_player; }

	// �V���b�g����
	Shot* createPlayerShot(VECTOR pos);
	Shot* createEnemyShot(VECTOR pos);

private:
	// �V�[�P���X�ɉ���������
	SceneBase* updateMain();			// kSeqMain,
	SceneBase* updateStageClear();	// kSeqStageClear,
	SceneBase* updateGameover();		// kSeqGameover,

	// �w�i����
	void initBg();
	void updateBg();
	void drawBg();

private:
	// variable ----------------------------------

	Seq	m_seq;

	int m_endWait;
	int m_fadeBright;

	// game
	Player m_player;
	Shot m_shot[cShotMax];

	StageManager	m_stage;
	Enemy m_enemy[cEnemyMax];

	// �O���t�B�b�N
	int m_playerGraphic;
	int m_shotGraphic;
	int m_enemyShotGraphic;
	int m_enemyGraphic;

	// �w�i
	GameObject	m_bgStar[cStarNum];
	// �G��|�������̃G�t�F�N�g����
	EffectManager m_effect;
};
