#include "PadUtil.h"

namespace Pad
{
	static const int cPadLogNum = 64;
	static int log[cPadLogNum];

	void clearLog()
	{
		for (int i = 0; i < cPadLogNum; i++)
		{
			log[i] = 0;
		}
	}
	void update()
	{
		for (int i = cPadLogNum - 1; i >= 1; i--)
		{
			log[i] = log[i - 1];
		}
		log[0] = GetJoypadInputState(DX_INPUT_KEY_PAD1);	// �L�[�{�[�h���g�p�\
	}

	// ���͏�Ԃ̎擾
	bool isTrigger(int inputType)
	{
		if (log[0] & inputType)
		{
			if (log[1] & inputType)	return false;
			return true;
		}
		return false;
	}

	bool isPress(int inputType)
	{
		return (log[0] & inputType);
	}
	// �Q�[���p�b�h�̐����擾
	int getPadNum()
	{
		return GetJoypadNum();
	}
};
