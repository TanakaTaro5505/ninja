#include "StageManager.h"
#include "Game.h"

#include "SceneMain.h"

// 敵生成情報
typedef struct EnemyCreateData
{
	int		frame;
	VECTOR	pos;
	int		hp;
}EnemyCreateData;

// ステージ情報
static const EnemyCreateData StageDataTbl_0[] =
{
	{  100, { Game::cScreenWidth + 64.0f, 100.0f }, 20 },
	{  200, { Game::cScreenWidth + 64.0f, 180.0f }, 20 },
	{  300, { Game::cScreenWidth + 64.0f, 260.0f }, 20 },
	{  400, { Game::cScreenWidth + 64.0f, 340.0f }, 20 },
	{  500, { Game::cScreenWidth + 64.0f, 420.0f }, 20 },

	{  700, { Game::cScreenWidth + 64.0f, 420.0f }, 20 },
	{  800, { Game::cScreenWidth + 64.0f, 340.0f }, 20 },
	{  900, { Game::cScreenWidth + 64.0f, 260.0f }, 20 },
	{ 1000, { Game::cScreenWidth + 64.0f, 180.0f }, 20 },
	{ 1200, { Game::cScreenWidth + 64.0f, 100.0f }, 20 },
};
static const int StageDataTblSize_0 = sizeof(StageDataTbl_0) / sizeof(StageDataTbl_0[0]);

void StageManager::init(SceneMain* pMain, int stageNo)
{
	m_pMain = pMain;
	m_stageNo = stageNo;

	m_frameCount = 0;
}

void StageManager::update()
{
	int lastFrame = m_frameCount;
	m_frameCount++;

	for (int i = 0; i < StageDataTblSize_0; i++)
	{
		if ((lastFrame < StageDataTbl_0[i].frame) &&
			(m_frameCount >= StageDataTbl_0[i].frame))
		{
			m_pMain->createEnemy(StageDataTbl_0[i].pos, StageDataTbl_0[i].hp);
		}
	}
}
