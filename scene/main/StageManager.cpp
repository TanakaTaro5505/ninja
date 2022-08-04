#include "StageManager.h"
#include "Game.h"

#include "SceneMain.h"

// 敵生成情報
typedef struct EnemyCreateData
{
	int			frame;
	VECTOR		pos;
	int			hp;
	Enemy::Type type;
}EnemyCreateData;

// ステージ情報
static const EnemyCreateData StageDataTbl_0[] =
{
	{   60, { Game::cScreenWidth + 64.0f, 100.0f }, 20, Enemy::Type::kTypeCharge },
	{  120, { Game::cScreenWidth + 64.0f, 180.0f }, 20, Enemy::Type::kTypeCharge },
	{  180, { Game::cScreenWidth + 64.0f, 260.0f }, 20, Enemy::Type::kTypeCharge },
	{  240, { Game::cScreenWidth + 64.0f, 340.0f }, 20, Enemy::Type::kTypeCharge },
	{  300, { Game::cScreenWidth + 64.0f, 420.0f }, 20, Enemy::Type::kTypeCharge },

	{  360, { Game::cScreenWidth + 64.0f, 420.0f }, 20, Enemy::Type::kTypeCharge },
	{  420, { Game::cScreenWidth + 64.0f, 340.0f }, 20, Enemy::Type::kTypeCharge },
	{  480, { Game::cScreenWidth + 64.0f, 260.0f }, 20, Enemy::Type::kTypeCharge },
	{  540, { Game::cScreenWidth + 64.0f, 180.0f }, 20, Enemy::Type::kTypeCharge },
	{  600, { Game::cScreenWidth + 64.0f, 100.0f }, 20, Enemy::Type::kTypeCharge },

	{  700, { Game::cScreenWidth + 64.0f, 160.0f }, 20, Enemy::Type::kTypeChargeSin },
	{  700, { Game::cScreenWidth + 64.0f, 260.0f }, 20, Enemy::Type::kTypeChargeSin },
	{  700, { Game::cScreenWidth + 64.0f, 360.0f }, 20, Enemy::Type::kTypeChargeSin },
	{  750, { Game::cScreenWidth + 64.0f, 100.0f }, 20, Enemy::Type::kTypeChargePlayer },

	{  800, { Game::cScreenWidth + 64.0f, 180.0f }, 20, Enemy::Type::kTypeChargeSin },
	{  800, { Game::cScreenWidth + 64.0f, 280.0f }, 20, Enemy::Type::kTypeChargeSin },
	{  800, { Game::cScreenWidth + 64.0f, 380.0f }, 20, Enemy::Type::kTypeChargeSin },
	{  850, { Game::cScreenWidth + 64.0f, 420.0f }, 20, Enemy::Type::kTypeChargePlayer },

	{  900, { Game::cScreenWidth + 64.0f, 160.0f }, 20, Enemy::Type::kTypeChargeSin },
	{  900, { Game::cScreenWidth + 64.0f, 260.0f }, 20, Enemy::Type::kTypeChargeSin },
	{  900, { Game::cScreenWidth + 64.0f, 360.0f }, 20, Enemy::Type::kTypeChargeSin },
	{  950, { Game::cScreenWidth + 64.0f, 100.0f }, 20, Enemy::Type::kTypeChargePlayer },

	{ 1000, { Game::cScreenWidth + 64.0f, 180.0f }, 20, Enemy::Type::kTypeChargeSin },
	{ 1000, { Game::cScreenWidth + 64.0f, 280.0f }, 20, Enemy::Type::kTypeChargeSin },
	{ 1000, { Game::cScreenWidth + 64.0f, 380.0f }, 20, Enemy::Type::kTypeChargeSin },
	{ 1050, { Game::cScreenWidth + 64.0f, 420.0f }, 20, Enemy::Type::kTypeChargePlayer },

	{ 1200, { Game::cScreenWidth + 64.0f, 100.0f }, 20, Enemy::Type::kTypeChargePlayer },
	{ 1210, { Game::cScreenWidth + 64.0f, 132.0f }, 20, Enemy::Type::kTypeChargePlayer },
	{ 1220, { Game::cScreenWidth + 64.0f, 164.0f }, 20, Enemy::Type::kTypeChargePlayer },
	{ 1230, { Game::cScreenWidth + 64.0f, 196.0f }, 20, Enemy::Type::kTypeChargePlayer },
	{ 1240, { Game::cScreenWidth + 64.0f, 228.0f }, 20, Enemy::Type::kTypeChargePlayer },
	{ 1250, { Game::cScreenWidth + 64.0f, 260.0f }, 20, Enemy::Type::kTypeChargePlayer },
	{ 1260, { Game::cScreenWidth + 64.0f, 292.0f }, 20, Enemy::Type::kTypeChargePlayer },
	{ 1270, { Game::cScreenWidth + 64.0f, 324.0f }, 20, Enemy::Type::kTypeChargePlayer },
	{ 1280, { Game::cScreenWidth + 64.0f, 356.0f }, 20, Enemy::Type::kTypeChargePlayer },
	{ 1290, { Game::cScreenWidth + 64.0f, 388.0f }, 20, Enemy::Type::kTypeChargePlayer },
	{ 1300, { Game::cScreenWidth + 64.0f, 420.0f }, 20, Enemy::Type::kTypeChargePlayer },

	{ 1310, { Game::cScreenWidth + 64.0f, 420.0f }, 20, Enemy::Type::kTypeChargePlayer },
	{ 1320, { Game::cScreenWidth + 64.0f, 388.0f }, 20, Enemy::Type::kTypeChargePlayer },
	{ 1330, { Game::cScreenWidth + 64.0f, 356.0f }, 20, Enemy::Type::kTypeChargePlayer },
	{ 1340, { Game::cScreenWidth + 64.0f, 324.0f }, 20, Enemy::Type::kTypeChargePlayer },
	{ 1350, { Game::cScreenWidth + 64.0f, 292.0f }, 20, Enemy::Type::kTypeChargePlayer },
	{ 1360, { Game::cScreenWidth + 64.0f, 260.0f }, 20, Enemy::Type::kTypeChargePlayer },
	{ 1370, { Game::cScreenWidth + 64.0f, 228.0f }, 20, Enemy::Type::kTypeChargePlayer },
	{ 1380, { Game::cScreenWidth + 64.0f, 196.0f }, 20, Enemy::Type::kTypeChargePlayer },
	{ 1390, { Game::cScreenWidth + 64.0f, 164.0f }, 20, Enemy::Type::kTypeChargePlayer },
	{ 1400, { Game::cScreenWidth + 64.0f, 132.0f }, 20, Enemy::Type::kTypeChargePlayer },
	{ 1410, { Game::cScreenWidth + 64.0f, 100.0f }, 20, Enemy::Type::kTypeChargePlayer },

	{ 1700, { Game::cScreenWidth + 64.0f, 270.0f }, 300, Enemy::Type::kTypeBoss00 },
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
			m_pMain->createEnemy(StageDataTbl_0[i].pos, StageDataTbl_0[i].hp, StageDataTbl_0[i].type);
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
