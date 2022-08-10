#include "StageManager.h"
#include "Game.h"

#include "SceneMain.h"

// �G�f�[�^
#include "EnemyMoveFront.h"
#include "EnemyMoveFrontSin.h"
#include "EnemyChargePlayer.h"
#include "EnemyBoss00.h"

// �G�̃^�C�v�ʃf�t�H���g�ݒ�
typedef struct EnemyDefaultStatus
{
	int hp;			// hp
	int hitDamage;	// �G�ɂԂ������Ƃ��̃_���[�W
	int shotDamage;	// �G�̃V���b�g�ɓ����������̃_���[�W
}EnemyDefaultStatus;

static constexpr EnemyDefaultStatus kEnemyStatus[static_cast<int>(StageManager::EnemyType::kEnemyTypeNum)] =
{
	{ 20, 10, 10 },		// kEnemyTypeCharge,		// �O�i����̂�
	{ 20, 10, 10 },		// 	kEnemyTypeChargeSin,	// �T�C���J�[�u�`���O�i
	{ 20, 10, 10 },		// 	kEnemyTypeChargePlayer,	// �v���C���[�ւ̓ːi

	{300,999, 20 },		// kEnemyTypeBoss00,		// �X�e�[�W1�{�X
};

// �G�������
typedef struct EnemyCreateData
{
	int			frame;
	VECTOR		pos;
	StageManager::EnemyType type;
}EnemyCreateData;

// ��̕���������5��
static const EnemyCreateData Parts_Charge5_U[] =
{
	{    0, { Game::cScreenWidth + 64.0f, 120.0f }, StageManager::EnemyType::kEnemyTypeCharge },
	{   60, { Game::cScreenWidth + 64.0f, 120.0f }, StageManager::EnemyType::kEnemyTypeCharge },
	{  120, { Game::cScreenWidth + 64.0f, 120.0f }, StageManager::EnemyType::kEnemyTypeCharge },
	{  180, { Game::cScreenWidth + 64.0f, 120.0f }, StageManager::EnemyType::kEnemyTypeCharge },
	{  240, { Game::cScreenWidth + 64.0f, 120.0f }, StageManager::EnemyType::kEnemyTypeCharge },
};
static constexpr int Parts_Charge5_U_Size = sizeof(Parts_Charge5_U) / sizeof(Parts_Charge5_U[0]);

// ���̕���������5��
static const EnemyCreateData Parts_Charge5_L[] =
{
	{    0, { Game::cScreenWidth + 64.0f, 420.0f }, StageManager::EnemyType::kEnemyTypeCharge },
	{   60, { Game::cScreenWidth + 64.0f, 420.0f }, StageManager::EnemyType::kEnemyTypeCharge },
	{  120, { Game::cScreenWidth + 64.0f, 420.0f }, StageManager::EnemyType::kEnemyTypeCharge },
	{  180, { Game::cScreenWidth + 64.0f, 420.0f }, StageManager::EnemyType::kEnemyTypeCharge },
	{  240, { Game::cScreenWidth + 64.0f, 420.0f }, StageManager::EnemyType::kEnemyTypeCharge },
};
static constexpr int Parts_Charge5_L_Size = sizeof(Parts_Charge5_L) / sizeof(Parts_Charge5_L[0]);

// ����T�C���J�[�u�Ō������Ă���R��+�v���C���[�ɓˌ�
static const EnemyCreateData Parts_SinCharge3_U[] =
{
	{    0, { Game::cScreenWidth + 64.0f, 160.0f }, StageManager::EnemyType::kEnemyTypeChargeSin },
	{    0, { Game::cScreenWidth + 64.0f, 260.0f }, StageManager::EnemyType::kEnemyTypeChargeSin },
	{    0, { Game::cScreenWidth + 64.0f, 360.0f }, StageManager::EnemyType::kEnemyTypeChargeSin },
	{   50, { Game::cScreenWidth + 64.0f, 100.0f }, StageManager::EnemyType::kEnemyTypeChargePlayer },
};
static constexpr int Parts_SinCharge3_U_Size = sizeof(Parts_SinCharge3_U) / sizeof(Parts_SinCharge3_U[0]);

// �����T�C���J�[�u�Ō������Ă���R��+�v���C���[�ɓˌ�
static const EnemyCreateData Parts_SinCharge3_L[] =
{
	{    0, { Game::cScreenWidth + 64.0f, 180.0f }, StageManager::EnemyType::kEnemyTypeChargeSin },
	{    0, { Game::cScreenWidth + 64.0f, 280.0f }, StageManager::EnemyType::kEnemyTypeChargeSin },
	{    0, { Game::cScreenWidth + 64.0f, 380.0f }, StageManager::EnemyType::kEnemyTypeChargeSin },
	{   50, { Game::cScreenWidth + 64.0f, 420.0f }, StageManager::EnemyType::kEnemyTypeChargePlayer },
};
static constexpr int Parts_SinCharge3_L_Size = sizeof(Parts_SinCharge3_L) / sizeof(Parts_SinCharge3_L[0]);

// �v���C���[�ɓˌ��@��������
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

// �p�[�c��g�ݍ��킹�ăX�e�[�W�f�[�^
typedef struct StagePartsData
{
	const EnemyCreateData*	data;		// nullptr���w�肵���ꍇ��dataSize�t���[���҂�
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
	// �f�[�^�͈͊O	�{�X����ē|���҂��̏ꍇ������̂ŃG���[�Ƃ��ł͂Ȃ�
	if (m_partsIndex >= StageDataSize_000)	return;


	int lastFrame = m_frameCount;
	m_frameCount++;

	const EnemyCreateData* pPartsTbl = StageData_000[m_partsIndex].data;
	int partsDataNum = StageData_000[m_partsIndex].dataSize;

	if (pPartsTbl)
	{
		// �G�f�[�^����
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

				// �Ō�̓G�𐶐����������
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
		// dataSize�ɓ����Ă���t���[���҂�
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
