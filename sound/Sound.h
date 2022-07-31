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

	// サウンドのロード、アンロード
	void Load();
	void Unload();
	
	// 効果音鳴らす
	void PlaySound(SoundID id);
};