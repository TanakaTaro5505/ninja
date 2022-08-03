#include "StageManager.h"
#include "Game.h"

#include "SceneMain.h"

// �G�������
typedef struct EnemyCreateData
{
	int			frame;
	VECTOR		pos;
	int			hp;
	Enemy::Type type;
}EnemyCreateData;

// �X�e�[�W���
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

	{  800, { Game::cScreenWidth + 64.0f, 180.0f }, 20, Enemy::Type::kTypeChargeSin },
	{  800, { Game::cScreenWidth + 64.0f, 280.0f }, 20, Enemy::Type::kTypeChargeSin },
	{  800, { Game::cScreenWidth + 64.0f, 380.0f }, 20, Enemy::Type::kTypeChargeSin },

	{  900, { Game::cScreenWidth + 64.0f, 160.0f }, 20, Enemy::Type::kTypeChargeSin },
	{  900, { Game::cScreenWidth + 64.0f, 260.0f }, 20, Enemy::Type::kTypeChargeSin },
	{  900, { Game::cScreenWidth + 64.0f, 360.0f }, 20, Enemy::Type::kTypeChargeSin },

	{ 1000, { Game::cScreenWidth + 64.0f, 180.0f }, 20, Enemy::Type::kTypeChargeSin },
	{ 1000, { Game::cScreenWidth + 64.0f, 280.0f }, 20, Enemy::Type::kTypeChargeSin },
	{ 1000, { Game::cScreenWidth + 64.0f, 380.0f }, 20, Enemy::Type::kTypeChargeSin },

	{ 1500, { Game::cScreenWidth + 64.0f, 270.0f }, 300, Enemy::Type::kTypeBoss00 },
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
