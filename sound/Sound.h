#pragma once

#include "DxLib.h"

namespace Sound
{
	typedef enum SoundID
	{
		kSoundID_Shot,
		kSoundID_Hit,

		kSoundID_Num
	}SoundID;

	// �T�E���h�̃��[�h�A�A�����[�h
	void Load();
	void Unload();
	
	// ���ʉ��炷
	void PlaySound(SoundID id);
};