#include "StageManager.h"
#include "Game.h"

#include "SceneMain.h"

// 敵データ
#include "EnemyMoveFront.h"
#include "EnemyMoveFrontSin.h"
#include "EnemyChargePlayer.h"
#include "EnemyBoss00.h"


// 敵生成情報
typedef struct EnemyCreateData
{
	int			frame;
	VECTOR		pos;
	int			hp;
	StageManager::EnemyType type;
}EnemyCreateData;

// ステージ情報
static const EnemyCreateData StageDataTbl_0[] =
{
	{   60, { Game::cScreenWidth + 64.0f, 100.0f }, 20, StageManager::EnemyType::kEnemyTypeCharge },
	{  120, { Game::cScreenWidth + 64.0f, 180.0f }, 20, StageManager::EnemyType::kEnemyTypeCharge },
	{  180, { Game::cScreenWidth + 64.0f, 260.0f }, 20, StageManager::EnemyType::kEnemyTypeCharge },
	{  240, { Game::cScreenWidth + 64.0f, 340.0f }, 20, StageManager::EnemyType::kEnemyTypeCharge },
	{  300, { Game::cScreenWidth + 64.0f, 420.0f }, 20, StageManager::EnemyType::kEnemyTypeCharge },

	{  360, { Game::cScreenWidth + 64.0f, 420.0f }, 20, StageManager::EnemyType::kEnemyTypeCharge },
	{  420, { Game::cScreenWidth + 64.0f, 340.0f }, 20, StageManager::EnemyType::kEnemyTypeCharge },
	{  480, { Game::cScreenWidth + 64.0f, 260.0f }, 20, StageManager::EnemyType::kEnemyTypeCharge },
	{  540, { Game::cScreenWidth + 64.0f, 180.0f }, 20, StageManager::EnemyType::kEnemyTypeCharge },
	{  600, { Game::cScreenWidth + 64.0f, 100.0f }, 20, StageManager::EnemyType::kEnemyTypeCharge },

	{  700, { Game::cScreenWidth + 64.0f, 160.0f }, 20, StageManager::EnemyType::kEnemyTypeChargeSin },
	{  700, { Game::cScreenWidth + 64.0f, 260.0f }, 20, StageManager::EnemyType::kEnemyTypeChargeSin },
	{  700, { Game::cScreenWidth + 64.0f, 360.0f }, 20, StageManager::EnemyType::kEnemyTypeChargeSin },
	{  750, { Game::cScreenWidth + 64.0f, 100.0f }, 20, StageManager::EnemyType::kEnemyTypeChargePlayer },

	{  800, { Game::cScreenWidth + 64.0f, 180.0f }, 20, StageManager::EnemyType::kEnemyTypeChargeSin },
	{  800, { Game::cScreenWidth + 64.0f, 280.0f }, 20, StageManager::EnemyType::kEnemyTypeChargeSin },
	{  800, { Game::cScreenWidth + 64.0f, 380.0f }, 20, StageManager::EnemyType::kEnemyTypeChargeSin },
	{  850, { Game::cScreenWidth + 64.0f, 420.0f }, 20, StageManager::EnemyType::kEnemyTypeChargePlayer },

	{  900, { Game::cScreenWidth + 64.0f, 160.0f }, 20, StageManager::EnemyType::kEnemyTypeChargeSin },
	{  900, { Game::cScreenWidth + 64.0f, 260.0f }, 20, StageManager::EnemyType::kEnemyTypeChargeSin },
	{  900, { Game::cScreenWidth + 64.0f, 360.0f }, 20, StageManager::EnemyType::kEnemyTypeChargeSin },
	{  950, { Game::cScreenWidth + 64.0f, 100.0f }, 20, StageManager::EnemyType::kEnemyTypeChargePlayer },

	{ 1000, { Game::cScreenWidth + 64.0f, 180.0f }, 20, StageManager::EnemyType::kEnemyTypeChargeSin },
	{ 1000, { Game::cScreenWidth + 64.0f, 280.0f }, 20, StageManager::EnemyType::kEnemyTypeChargeSin },
	{ 1000, { Game::cScreenWidth + 64.0f, 380.0f }, 20, StageManager::EnemyType::kEnemyTypeChargeSin },
	{ 1050, { Game::cScreenWidth + 64.0f, 420.0f }, 20, StageManager::EnemyType::kEnemyTypeChargePlayer },

	{ 1200, { Game::cScreenWidth + 64.0f, 100.0f }, 20, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{ 1210, { Game::cScreenWidth + 64.0f, 132.0f }, 20, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{ 1220, { Game::cScreenWidth + 64.0f, 164.0f }, 20, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{ 1230, { Game::cScreenWidth + 64.0f, 196.0f }, 20, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{ 1240, { Game::cScreenWidth + 64.0f, 228.0f }, 20, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{ 1250, { Game::cScreenWidth + 64.0f, 260.0f }, 20, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{ 1260, { Game::cScreenWidth + 64.0f, 292.0f }, 20, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{ 1270, { Game::cScreenWidth + 64.0f, 324.0f }, 20, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{ 1280, { Game::cScreenWidth + 64.0f, 356.0f }, 20, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{ 1290, { Game::cScreenWidth + 64.0f, 388.0f }, 20, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{ 1300, { Game::cScreenWidth + 64.0f, 420.0f }, 20, StageManager::EnemyType::kEnemyTypeChargePlayer },

	{ 1310, { Game::cScreenWidth + 64.0f, 420.0f }, 20, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{ 1320, { Game::cScreenWidth + 64.0f, 388.0f }, 20, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{ 1330, { Game::cScreenWidth + 64.0f, 356.0f }, 20, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{ 1340, { Game::cScreenWidth + 64.0f, 324.0f }, 20, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{ 1350, { Game::cScreenWidth + 64.0f, 292.0f }, 20, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{ 1360, { Game::cScreenWidth + 64.0f, 260.0f }, 20, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{ 1370, { Game::cScreenWidth + 64.0f, 228.0f }, 20, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{ 1380, { Game::cScreenWidth + 64.0f, 196.0f }, 20, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{ 1390, { Game::cScreenWidth + 64.0f, 164.0f }, 20, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{ 1400, { Game::cScreenWidth + 64.0f, 132.0f }, 20, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{ 1410, { Game::cScreenWidth + 64.0f, 100.0f }, 20, StageManager::EnemyType::kEnemyTypeChargePlayer },

	{ 1700, { Game::cScreenWidth + 64.0f, 270.0f }, 300, StageManager::EnemyType::kEnemyTypeBoss00 },
};
static constexpr int StageDataTblSize_0 = sizeof(StageDataTbl_0) / sizeof(StageDataTbl_0[0]);

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
#if false
			m_pMain->createEnemy(StageDataTbl_0[i].pos, StageDataTbl_0[i].hp, StageDataTbl_0[i].type);
#else
			EnemyBase* pEnemy = nullptr;
			switch (StageDataTbl_0[i].type)
			{
			case EnemyType::kEnemyTypeCharge:
				pEnemy = new EnemyMoveFront;
				break;
			case EnemyType::kEnemyTypeChargeSin:
				pEnemy = new EnemyMoveFrontSin;
				break;
			case EnemyType::kEnemyTypeChargePlayer:
				pEnemy = new EnemyChargePlayer;
				break;
			case EnemyType::kEnemyTypeBoss00:
				pEnemy = new EnemyBoss00;
				break;

			default:
				pEnemy = new EnemyMoveFront;
				break;
			}

			pEnemy->createGraphic(StageDataTbl_0[i].pos.x, StageDataTbl_0[i].pos.y, m_pMain->getEnemyGraphic());
			pEnemy->setMain(m_pMain);

			pEnemy->init(StageDataTbl_0[i].hp);
			pEnemy->setHitDamage(8);
			pEnemy->setShotDamage(8);

			m_pMain->addEnemy(pEnemy);
#endif
		}
	}
}

bool StageManager::isEnd()
{
	if (m_frameCount > StageDataTbl_0[StageDataTblSize_0 - 1].frame)
	{
		return true;
	}
	return false;
}
