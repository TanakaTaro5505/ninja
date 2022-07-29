#pragma once

class SceneMain;

class StageManager
{
public:
	StageManager()
	{
		m_pMain = nullptr;
		m_stageNo = 0;
		m_frameCount = 0;
	}
	virtual ~StageManager()
	{
	}

	void init(SceneMain* pMain, int stageNo);
	void update();

	int getFrame() const { return m_frameCount; }

private:

	SceneMain* m_pMain;

	int		m_stageNo;
	int		m_frameCount;
};