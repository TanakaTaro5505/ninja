#pragma once
#include "DxLib.h"
#include <list>
#include "SceneManager.h"
#include "PadUtil.h"

#include "Command.h"
#include "Player.h"
#include "Shot.h"
#include "Enemy.h"
#include "Item.h"
#include "StageManager.h"

#include "Effect/EffectManager.h"

class SceneMain : public SceneBase
{
	//define ----------------------------------
private:
	static constexpr int kShotMax = 128;

	static constexpr int kStarNum = 64;

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
		m_itemGraphic = 0;

		m_clearGraphic = 0;
		m_gameoverGraphic = 0;
	}
	virtual ~SceneMain()
	{
		deleteGraph();
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

	// �A�C�e������
	void createItem(VECTOR pos);

private:
	// �V�[�P���X�ɉ���������
	SceneBase* updateMain();		// kSeqMain,
	SceneBase* updateStageClear();	// kSeqStageClear,
	SceneBase* updateGameover();	// kSeqGameover,

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
	std::list<Shot*>	m_shotList;

	StageManager	m_stage;
	std::list<Enemy*>	m_enemyList;
	std::list<Item*>	m_itemList;

	// �O���t�B�b�N
	int m_playerGraphic;
	int m_shotGraphic;
	int m_enemyShotGraphic;
	int m_enemyGraphic;
	int m_itemGraphic;

	int m_clearGraphic;
	int m_gameoverGraphic;

	// �w�i
	GameObject	m_bgStar[kStarNum];
	// �G��|�������̃G�t�F�N�g����
	EffectManager m_effect;
};
