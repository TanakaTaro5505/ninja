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

// 上の方から並んで5体
static const EnemyCreateData StagePartsData_000[] =
{
	{    0, { Game::cScreenWidth + 64.0f, 100.0f }, 20, StageManager::EnemyType::kEnemyTypeCharge },
	{   60, { Game::cScreenWidth + 64.0f, 100.0f }, 20, StageManager::EnemyType::kEnemyTypeCharge },
	{  120, { Game::cScreenWidth + 64.0f, 100.0f }, 20, StageManager::EnemyType::kEnemyTypeCharge },
	{  180, { Game::cScreenWidth + 64.0f, 100.0f }, 20, StageManager::EnemyType::kEnemyTypeCharge },
	{  240, { Game::cScreenWidth + 64.0f, 100.0f }, 20, StageManager::EnemyType::kEnemyTypeCharge },
};
static constexpr int StagePartsDataSize_000 = sizeof(StagePartsData_000) / sizeof(StagePartsData_000[0]);

// 下の方から並んで5体
static const EnemyCreateData StagePartsData_001[] =
{
	{    0, { Game::cScreenWidth + 64.0f, 440.0f }, 20, StageManager::EnemyType::kEnemyTypeCharge },
	{   60, { Game::cScreenWidth + 64.0f, 440.0f }, 20, StageManager::EnemyType::kEnemyTypeCharge },
	{  120, { Game::cScreenWidth + 64.0f, 440.0f }, 20, StageManager::EnemyType::kEnemyTypeCharge },
	{  180, { Game::cScreenWidth + 64.0f, 440.0f }, 20, StageManager::EnemyType::kEnemyTypeCharge },
	{  240, { Game::cScreenWidth + 64.0f, 440.0f }, 20, StageManager::EnemyType::kEnemyTypeCharge },
};
static constexpr int StagePartsDataSize_001 = sizeof(StagePartsData_001) / sizeof(StagePartsData_001[0]);



static const EnemyCreateData StagePartsData_Boss_000[] =
{
	{    0, { Game::cScreenWidth + 64.0f, 270.0f }, 300, StageManager::EnemyType::kEnemyTypeBoss00 },
};
static constexpr int StagePartsDataSize_Boss_000 = sizeof(StagePartsData_Boss_000) / sizeof(StagePartsData_Boss_000[0]);

// パーツを組み合わせてステージデータ
typedef struct StagePartsData
{
	const EnemyCreateData*	data;		// nullptrを指定した場合はdataSizeフレーム待つ
	int						dataSize;
}StagePartsData;

static constexpr StagePartsData StageData_000[] =
{
	{ nullptr					, 60 },
	{ StagePartsData_000		, StagePartsDataSize_000 },
	{ nullptr					, 120 },
	{ StagePartsData_001		, StagePartsDataSize_001 },
	{ nullptr					, 180 },
	{ StagePartsData_Boss_000	, StagePartsDataSize_Boss_000 }
};
static constexpr int StageDataSize_000 = sizeof(StageData_000) / sizeof(StageData_000[0]);

void StageManager::init(SceneMain* pMain, int stageNo)
{
	m_pMain = pMain;
	m_stageNo = stageNo;

	m_partsIndex = 0;
	m_frameCount = -1;
}

void StageManager::update()
{
	// データ範囲外	ボス作って倒し待ちの場合もあるのでエラーとかではない
	if (m_partsIndex >= StageDataSize_000)	return;


	int lastFrame = m_frameCount;
	m_frameCount++;

	const EnemyCreateData* pPartsTbl = StageData_000[m_partsIndex].data;
	int partsDataNum = StageData_000[m_partsIndex].dataSize;

	if (pPartsTbl)
	{
		for (int i = 0; i < partsDataNum; i++)
		{
			if ((lastFrame < pPartsTbl[i].frame) &&
				(m_frameCount >= pPartsTbl[i].frame))
			{
				EnemyBase* pEnemy = nullptr;
				switch (pPartsTbl[i].type)
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

				pEnemy->createGraphic(pPartsTbl[i].pos.x, pPartsTbl[i].pos.y, m_pMain->getEnemyGraphic());
				pEnemy->setMain(m_pMain);

				pEnemy->init(pPartsTbl[i].hp);
				pEnemy->setHitDamage(8);
				pEnemy->setShotDamage(8);

				m_pMain->addEnemy(pEnemy);

				// 最後の敵を生成したらつぎへ
				if (i >= partsDataNum-1)
				{
					m_partsIndex++;
					m_frameCount = -1;
				}
			}
		}
	}
	else
	{
		// dataSizeに入っているフレーム待つ
		if (m_frameCount >= partsDataNum)
		{
			m_partsIndex++;
			m_frameCount = -1;
		}
	}
}

bool StageManager::isEnd()
{
	if (m_partsIndex >= StageDataSize_000)	return true;
	return false;
}
