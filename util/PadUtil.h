#pragma once

#include "DxLib.h"

namespace Pad
{
	void clearLog();
	void update();

	// ���͏�Ԃ̎擾
	bool isTrigger(int inputType);
	bool isPress(int inputType);

	// �Q�[���p�b�h�̐����擾
	int getPadNum();
};