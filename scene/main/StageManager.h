#pragma once

class SceneMain;

class StageManager
{
public:
	enum class EnemyType
	{
		kEnemyTypeCharge,		// 前進するのみ
		kEnemyTypeChargeSin,	// サインカーブ描く前進
		kEnemyTypeChargePlayer,	// プレイヤーへの突進
			// 弾撃って逃げる

		kEnemyTypeBoss00,		// ステージ1ボス

		kEnemyTypeNum
	};
public:
	StageManager()
	{
		m_pMain = nullptr;
		m_stageNo = 0;
		m_partsIndex = 0;
		m_frameCount = 0;
	}
	virtual ~StageManager()
	{
	}

	void init(SceneMain* pMain, int stageNo);
	void update();

	int getFrame() const { return m_frameCount; }

	// すべての敵を生成済み
	bool isEnd();

private:

	SceneMain* m_pMain;

	int		m_stageNo;
	int		m_partsIndex;
	int		m_frameCount;
};