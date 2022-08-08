#pragma once

#include "DxLib.h"

namespace Sound
{
	typedef enum SoundID
	{
		// タイトル画面
		kSoundID_Start,
		// メイン
		kSoundID_Shot,
		kSoundID_Hit,
		kSoundID_Dead,
		kSoundID_Levelup,

		kSoundID_Num
	}SoundID;

	// サウンドのロード、アンロード
	void Load();
	void Unload();
	
	// 効果音鳴らす
	void PlaySound(SoundID id);
};