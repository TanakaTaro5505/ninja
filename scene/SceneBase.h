#pragma once
#include "PadUtil.h"
#include "SceneManager.h"

class SceneManager;

class SceneBase
{
//function ----------------------------------
public:
	SceneBase() {}
	virtual ~SceneBase() {}

	virtual void init() = 0;
	virtual SceneBase* update() = 0;
	virtual void draw() = 0;

//variable ----------------------------------

};
