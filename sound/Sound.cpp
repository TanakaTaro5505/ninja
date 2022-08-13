#include "Sound.h"

namespace Sound
{
	static const char* const kSoundFileName[kSoundID_Num] =
	{
		"data/sound/bgmPlay.mp3",	// kSoundID_BgmPlay,

		"data/sound/start.mp3",	// kSoundID_Start,

		"data/sound/shot.mp3",	// kSoundID_Shot,
		"data/sound/hit.mp3",	// kSoundID_Hit,
		"data/sound/dead.mp3",	// kSoundID_Dead,
		"data/sound/levelup.mp3",	// kSoundID_Levelup,
		"data/sound/enemyDead.mp3",	// kSoundID_EnemyDead
		"data/sound/bossAttack.mp3",	// kSoundID_BossAttack
		"data/sound/bossDead.mp3",		// kSoundID_BossDead
	};

	static int soundHandle[kSoundID_Num];

	void Load()
	{
		for (int i = 0; i < kSoundID_Num; i++)
		{
			soundHandle[i] = LoadSoundMem(kSoundFileName[i]);
			ChangeVolumeSoundMem(128, soundHandle[i]);
		}
	}

	void Unload()
	{
		for (int i = 0; i < kSoundID_Num; i++)
		{
			DeleteSoundMem(soundHandle[i]);
		}
	}

	void PlayBgm(SoundID id)
	{
		PlaySoundMem(soundHandle[id], DX_PLAYTYPE_LOOP, TRUE);
	}
	void StopBgm(SoundID id)
	{
		StopSoundMem(soundHandle[id]);
	}

	void PlaySound(SoundID id)
	{
		PlaySoundMem(soundHandle[id], DX_PLAYTYPE_BACK, TRUE);
	}
};
