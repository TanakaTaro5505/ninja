#pragma once
#include "DxLib.h"
#include <vector>
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

		m_levelUpPos = {-999.0f, -999.0f, -999.0f};
		m_pLevelupText = nullptr;
		m_levelupDispFrame = -1;
#if false
		for (int i = 0; i < kGraphicData_Kind; i++)
		{
			m_graphicHandle[i] = -1;
		}
#endif
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
	Shot* createPlayerShot(Vec2 pos);
	Shot* createEnemyShot(Vec2 pos);
	// はじけ演出作成
	void createDeadEffect(Vec2 pos);
	// アイテム生成
	void createItem(Vec2 pos);
	// posから一番近くにいる敵の位置取得	敵がいない場合false
	bool getNearEnemyPos(Vec2* pOut, Vec2 pos);

	int getEnemyGraphic() { return m_graphicHandle[kGraphicData_Enemy]; }

	// レベルアップ演出開始
	void setLevelup(Vec2 pos, const char* text );

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

	// レベルアップ演出
	VECTOR m_levelUpPos;

	const char* m_pLevelupText;
	int m_levelupDispFrame;

	// グラフィック
	std::vector<int>	m_graphicHandle;
	// 背景
	GameObject	m_bgStar[kStarNum];
	// 敵を倒した時のエフェクト生成
	EffectManager m_effect;
};
