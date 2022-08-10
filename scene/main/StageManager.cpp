#include "StageManager.h"
#include "Game.h"

#include "SceneMain.h"

// 敵データ
#include "EnemyMoveFront.h"
#include "EnemyMoveFrontSin.h"
#include "EnemyChargePlayer.h"
#include "EnemyBoss00.h"

// 敵のタイプ別デフォルト設定
typedef struct EnemyDefaultStatus
{
	int hp;			// hp
	int hitDamage;	// 敵にぶつかったときのダメージ
	int shotDamage;	// 敵のショットに当たった時のダメージ
}EnemyDefaultStatus;

static constexpr EnemyDefaultStatus kEnemyStatus[static_cast<int>(StageManager::EnemyType::kEnemyTypeNum)] =
{
	{ 20, 10, 10 },		// kEnemyTypeCharge,		// 前進するのみ
	{ 20, 10, 10 },		// 	kEnemyTypeChargeSin,	// サインカーブ描く前進
	{ 20, 10, 10 },		// 	kEnemyTypeChargePlayer,	// プレイヤーへの突進

	{300,999, 20 },		// kEnemyTypeBoss00,		// ステージ1ボス
};

// 敵生成情報
typedef struct EnemyCreateData
{
	int			frame;
	VECTOR		pos;
	StageManager::EnemyType type;
}EnemyCreateData;

// 上の方から並んで5体
static const EnemyCreateData Parts_Charge5_U[] =
{
	{    0, { Game::cScreenWidth + 64.0f, 120.0f }, StageManager::EnemyType::kEnemyTypeCharge },
	{   60, { Game::cScreenWidth + 64.0f, 120.0f }, StageManager::EnemyType::kEnemyTypeCharge },
	{  120, { Game::cScreenWidth + 64.0f, 120.0f }, StageManager::EnemyType::kEnemyTypeCharge },
	{  180, { Game::cScreenWidth + 64.0f, 120.0f }, StageManager::EnemyType::kEnemyTypeCharge },
	{  240, { Game::cScreenWidth + 64.0f, 120.0f }, StageManager::EnemyType::kEnemyTypeCharge },
};
static constexpr int Parts_Charge5_U_Size = sizeof(Parts_Charge5_U) / sizeof(Parts_Charge5_U[0]);

// 下の方から並んで5体
static const EnemyCreateData Parts_Charge5_L[] =
{
	{    0, { Game::cScreenWidth + 64.0f, 420.0f }, StageManager::EnemyType::kEnemyTypeCharge },
	{   60, { Game::cScreenWidth + 64.0f, 420.0f }, StageManager::EnemyType::kEnemyTypeCharge },
	{  120, { Game::cScreenWidth + 64.0f, 420.0f }, StageManager::EnemyType::kEnemyTypeCharge },
	{  180, { Game::cScreenWidth + 64.0f, 420.0f }, StageManager::EnemyType::kEnemyTypeCharge },
	{  240, { Game::cScreenWidth + 64.0f, 420.0f }, StageManager::EnemyType::kEnemyTypeCharge },
};
static constexpr int Parts_Charge5_L_Size = sizeof(Parts_Charge5_L) / sizeof(Parts_Charge5_L[0]);

// 上よりサインカーブで向かってくる３体+プレイヤーに突撃
static const EnemyCreateData Parts_SinCharge3_U[] =
{
	{    0, { Game::cScreenWidth + 64.0f, 160.0f }, StageManager::EnemyType::kEnemyTypeChargeSin },
	{    0, { Game::cScreenWidth + 64.0f, 260.0f }, StageManager::EnemyType::kEnemyTypeChargeSin },
	{    0, { Game::cScreenWidth + 64.0f, 360.0f }, StageManager::EnemyType::kEnemyTypeChargeSin },
	{   50, { Game::cScreenWidth + 64.0f, 100.0f }, StageManager::EnemyType::kEnemyTypeChargePlayer },
};
static constexpr int Parts_SinCharge3_U_Size = sizeof(Parts_SinCharge3_U) / sizeof(Parts_SinCharge3_U[0]);

// 下よりサインカーブで向かってくる３体+プレイヤーに突撃
static const EnemyCreateData Parts_SinCharge3_L[] =
{
	{    0, { Game::cScreenWidth + 64.0f, 180.0f }, StageManager::EnemyType::kEnemyTypeChargeSin },
	{    0, { Game::cScreenWidth + 64.0f, 280.0f }, StageManager::EnemyType::kEnemyTypeChargeSin },
	{    0, { Game::cScreenWidth + 64.0f, 380.0f }, StageManager::EnemyType::kEnemyTypeChargeSin },
	{   50, { Game::cScreenWidth + 64.0f, 420.0f }, StageManager::EnemyType::kEnemyTypeChargePlayer },
};
static constexpr int Parts_SinCharge3_L_Size = sizeof(Parts_SinCharge3_L) / sizeof(Parts_SinCharge3_L[0]);

// プレイヤーに突撃　たくさん
static const EnemyCreateData Parts_PlayerChargeRush_00[] =
{
	{   0, { Game::cScreenWidth + 64.0f, 100.0f }, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{  10, { Game::cScreenWidth + 64.0f, 132.0f }, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{  20, { Game::cScreenWidth + 64.0f, 164.0f }, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{  30, { Game::cScreenWidth + 64.0f, 196.0f }, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{  40, { Game::cScreenWidth + 64.0f, 228.0f }, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{  50, { Game::cScreenWidth + 64.0f, 260.0f }, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{  60, { Game::cScreenWidth + 64.0f, 292.0f }, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{  70, { Game::cScreenWidth + 64.0f, 324.0f }, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{  80, { Game::cScreenWidth + 64.0f, 356.0f }, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{  90, { Game::cScreenWidth + 64.0f, 388.0f }, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{ 100, { Game::cScreenWidth + 64.0f, 420.0f }, StageManager::EnemyType::kEnemyTypeChargePlayer },
};
static constexpr int Parts_PlayerChargeRush_00_Size = sizeof(Parts_PlayerChargeRush_00) / sizeof(Parts_PlayerChargeRush_00[0]);

static const EnemyCreateData Parts_PlayerChargeRush_01[] =
{
	{  10, { Game::cScreenWidth + 64.0f, 420.0f }, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{  20, { Game::cScreenWidth + 64.0f, 388.0f }, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{  30, { Game::cScreenWidth + 64.0f, 356.0f }, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{  40, { Game::cScreenWidth + 64.0f, 324.0f }, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{  50, { Game::cScreenWidth + 64.0f, 292.0f }, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{  60, { Game::cScreenWidth + 64.0f, 260.0f }, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{  70, { Game::cScreenWidth + 64.0f, 228.0f }, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{  80, { Game::cScreenWidth + 64.0f, 196.0f }, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{  90, { Game::cScreenWidth + 64.0f, 164.0f }, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{ 100, { Game::cScreenWidth + 64.0f, 132.0f }, StageManager::EnemyType::kEnemyTypeChargePlayer },
	{ 110, { Game::cScreenWidth + 64.0f, 100.0f }, StageManager::EnemyType::kEnemyTypeChargePlayer },
};
static constexpr int Parts_PlayerChargeRush_01_Size = sizeof(Parts_PlayerChargeRush_01) / sizeof(Parts_PlayerChargeRush_01[0]);

static const EnemyCreateData Parts_Boss000[] =
{
	{    0, { Game::cScreenWidth + 64.0f, 270.0f }, StageManager::EnemyType::kEnemyTypeBoss00 },
};
static constexpr int Parts_Boss000_Size = sizeof(Parts_Boss000) / sizeof(Parts_Boss000[0]);

// パーツを組み合わせてステージデータ
typedef struct StagePartsData
{
	const EnemyCreateData*	data;		// nullptrを指定した場合はdataSizeフレーム待つ
	int						dataSize;
}StagePartsData;

static constexpr StagePartsData StageData_000[] =
{
	{ nullptr					,  60 },
	{ Parts_Charge5_U			, Parts_Charge5_U_Size },
	{ nullptr					,  60 },
	{ Parts_Charge5_L			, Parts_Charge5_L_Size },
	{ nullptr					,  60 },
	{ Parts_Charge5_U			, Parts_Charge5_U_Size },
	{ nullptr					,  60 },
	{ Parts_Charge5_L			, Parts_Charge5_L_Size },

	{ nullptr					, 120 },
	{ Parts_SinCharge3_U		, Parts_SinCharge3_U_Size },
	{ nullptr					, 120 },
	{ Parts_SinCharge3_L		, Parts_SinCharge3_L_Size },
	{ nullptr					, 120 },
	{ Parts_SinCharge3_U		, Parts_SinCharge3_U_Size },
	{ nullptr					, 120 },
	{ Parts_SinCharge3_L		, Parts_SinCharge3_L_Size },
	{ nullptr					,  60 },
	{ Parts_PlayerChargeRush_00	, Parts_PlayerChargeRush_00_Size },
	{ nullptr					,  10 },
	{ Parts_PlayerChargeRush_01	, Parts_PlayerChargeRush_01_Size },
	

	{ nullptr			, 180 },
	{ Parts_Boss000		, Parts_Boss000_Size }
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
		// 敵データあり
		for (int i = 0; i < partsDataNum; i++)
		{
			if ((lastFrame < pPartsTbl[i].frame) &&
				(m_frameCount >= pPartsTbl[i].frame))
			{
				EnemyBase* pEnemy = createEnemy(pPartsTbl[i].type);
				pEnemy->createGraphic(pPartsTbl[i].pos.x, pPartsTbl[i].pos.y, m_pMain->getEnemyGraphic());
				pEnemy->setMain(m_pMain);

				EnemyDefaultStatus status = kEnemyStatus[static_cast<int>(pPartsTbl[i].type)];
				pEnemy->init(status.hp);
				pEnemy->setHitDamage(status.hitDamage);
				pEnemy->setShotDamage(status.shotDamage);

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

EnemyBase* StageManager::createEnemy(EnemyType type)
{
	EnemyBase* pEnemy = nullptr;
	switch (type)
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
	return pEnemy;
}
