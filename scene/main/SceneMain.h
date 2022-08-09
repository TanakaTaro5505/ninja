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
	// �O���t�B�b�N�f�[�^
	typedef enum GraphicData
	{
		kGraphicData_Player,
		kGraphicData_Shot,
		kGraphicData_Enemy,
		kGraphicData_EnemyShot,
		kGraphicData_Item,

		// �����n
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

	// �G����
	void addEnemy(EnemyBase* pEnemy);

	// �v���C���[�擾
	Player* getPlayer() { return &m_player; }

	// �V���b�g����
	Shot* createPlayerShot(VECTOR pos);
	Shot* createEnemyShot(VECTOR pos);

	// �A�C�e������
	void createItem(VECTOR pos);

	int getEnemyGraphic() { return m_graphicHandle[kGraphicData_Enemy]; }

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
	int m_frameCount;

	int m_endWait;
	int m_fadeBright;

	// game
	Player m_player;
	std::list<Shot*>	m_shotList;

	StageManager	m_stage;
	std::list<EnemyBase*>	m_enemyList;
	std::list<Item*>	m_itemList;

	// �O���t�B�b�N
	int m_graphicHandle[kGraphicData_Kind];
	// �w�i
	GameObject	m_bgStar[kStarNum];
	// �G��|�������̃G�t�F�N�g����
	EffectManager m_effect;
};
