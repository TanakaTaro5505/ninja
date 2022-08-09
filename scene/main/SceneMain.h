#pragma once
#include "DxLib.h"
#include <list>
#include "SceneManager.h"
#include "PadUtil.h"

#include "Command.h"
#include "Player.h"
#include "Shot.h"
#include "EnemyBase.h"
#include "Item.h"
#include "StageManager.h"

#include "Effect/EffectManager.h"

class SceneMain : public SceneBase
{
	//define ----------------------------------
public:
	// グラフィックデータ
	typedef enum GraphicData
	{
		kGraphicData_Player,
		kGraphicData_Shot,
		kGraphicData_Enemy,
		kGraphicData_EnemyShot,
		kGraphicData_Item,

		// 文字系
		kGraphicData_LevelUp,
		kGraphicData_Clear,
		kGraphicData_Gameover,

		kGraphicData_Kind
	}GraphicData;
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
		m_frameCount = 0;
		m_endWait = -1;
		m_fadeBright = 0;

		for (int i = 0; i < kGraphicData_Kind; i++)
		{
			m_graphicHandle[i] = -1;
		}
	}
	virtual ~SceneMain()
	{
		deleteGraph();
	}

	void init();
	void deleteGraph();
	SceneBase* update();
	void draw();

	// 敵生成
	void addEnemy(EnemyBase* pEnemy);

	// プレイヤー取得
	Player* getPlayer() { return &m_player; }

	// ショット生成
	Shot* createPlayerShot(VECTOR pos);
	Shot* createEnemyShot(VECTOR pos);

	// アイテム生成
	void createItem(VECTOR pos);

	int getEnemyGraphic() { return m_graphicHandle[kGraphicData_Enemy]; }

private:
	// シーケンスに応じた処理
	SceneBase* updateMain();		// kSeqMain,
	SceneBase* updateStageClear();	// kSeqStageClear,
	SceneBase* updateGameover();	// kSeqGameover,

	// 背景処理
	void initBg();
	void updateBg();
	void drawBg();

private:
	// variable ----------------------------------

	Seq	m_seq;
	int m_frameCount;

	int m_endWait;
	int m_fadeBright;

	// game
	Player m_player;
	std::list<Shot*>	m_shotList;

	StageManager	m_stage;
	std::list<EnemyBase*>	m_enemyList;
	std::list<Item*>	m_itemList;

	// グラフィック
	int m_graphicHandle[kGraphicData_Kind];
	// 背景
	GameObject	m_bgStar[kStarNum];
	// 敵を倒した時のエフェクト生成
	EffectManager m_effect;
};
