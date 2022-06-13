#pragma once
#include "SceneBase.h"
#include "PadUtil.h"

#include "title/SceneTitle.h"
#include "main/SceneMain.h"

class SceneBase;

class SceneManager
{
public:

//function ----------------------------------
public:
	SceneManager();
	virtual ~SceneManager();

	void change(SceneBase* scene);
	void update();
	void draw();

//variable ----------------------------------
private:
	SceneBase* m_pScene;
};
