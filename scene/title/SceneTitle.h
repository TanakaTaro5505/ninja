#pragma once
#include "DxLib.h"
#include "SceneManager.h"
#include "PadUtil.h"

#include "Command.h"

class SceneTitle :public SceneBase
{
	//define ----------------------------------
private:

	//function ----------------------------------
public:
	SceneTitle() : SceneBase()
	{
		m_titleGraphic = -1;

		m_endWait = -1;
		m_fadeBright = 0;
	}
	virtual ~SceneTitle()
	{
		deleteGraph();
	}

	void init();
	void deleteGraph();
	SceneBase* update();
	void draw();

private:
	// ¶‰E’†‰›ˆÊ’u‚É•¶š—ñ•\¦
	void DrawStringCenter( int y, const char* str );

	// variable ----------------------------------
private:
	int m_titleGraphic;

	int m_endWait;
	int m_fadeBright;
};
