#pragma once

#include "DxLib.h"

namespace Sound
{
	typedef enum SoundID
	{
		// �^�C�g�����
		kSoundID_Start,
		// ���C��
		kSoundID_Shot,
		kSoundID_Hit,
		kSoundID_Dead,
		kSoundID_Levelup,

		kSoundID_Num
	}SoundID;

	// �T�E���h�̃��[�h�A�A�����[�h
	void Load();
	void Unload();
	
	// ���ʉ��炷
	void PlaySound(SoundID id);
};