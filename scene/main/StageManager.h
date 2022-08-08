#pragma once

class SceneMain;

class StageManager
{
public:
	enum class EnemyType
	{
		kEnemyTypeCharge,		// �O�i����̂�
		kEnemyTypeChargeSin,	// �T�C���J�[�u�`���O�i
		kEnemyTypeChargePlayer,	// �v���C���[�ւ̓ːi
			// �e�����ē�����

		kEnemyTypeBoss00,		// �X�e�[�W1�{�X

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

	// ���ׂĂ̓G�𐶐��ς�
	bool isEnd();

private:

	SceneMain* m_pMain;

	int		m_stageNo;
	int		m_partsIndex;
	int		m_frameCount;
};