#pragma once

#include "DxLib.h"

namespace Sound
{
	typedef enum SoundID
	{
		// bgm
		kSoundID_BgmPlay,

		// タイトル画面
		kSoundID_Start,
		// メイン
		kSoundID_Shot,
		kSoundID_Hit,
		kSoundID_Dead,
		kSoundID_Levelup,
		kSoundID_EnemyDead,
		kSoundID_BossAttack,
		kSoundID_BossDead,

		kSoundID_Num
	}SoundID;

	// サウンドのロード、アンロード
	void Load();
	void Unload();
	
	// BGM鳴らす(ループ再生)
	void PlayBgm(SoundID id);
	void StopBgm(SoundID id);

	// 効果音鳴らす
	void PlaySound(SoundID id);
};