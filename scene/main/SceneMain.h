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

	// 敵生成
	void createEnemy(VECTOR pos, int hp, Enemy::Type type);

	// プレイヤー取得
	Player* getPlayer() { return &m_player; }

	// ショット生成
	Shot* createPlayerShot(VECTOR pos);
	Shot* createEnemyShot(VECTOR pos);

private:
	// シーケンスに応じた処理
	SceneBase* updateMain();			// kSeqMain,
	SceneBase* updateStageClear();	// kSeqStageClear,
	SceneBase* updateGameover();		// kSeqGameover,

	// 背景処理
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

	// グラフィック
	int m_playerGraphic;
	int m_shotGraphic;
	int m_enemyShotGraphic;
	int m_enemyGraphic;

	// 背景
	GameObject	m_bgStar[cStarNum];
	// 敵を倒した時のエフェクト生成
	EffectManager m_effect;
};
