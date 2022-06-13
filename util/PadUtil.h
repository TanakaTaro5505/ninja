#pragma once

#include "DxLib.h"

namespace Pad
{
	void clearLog();
	void update();

	// 入力状態の取得
	bool isTrigger(int inputType);
	bool isPress(int inputType);

	// ゲームパッドの数を取得
	int getPadNum();
};