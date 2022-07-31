#include "Sound.h"

namespace Sound
{
	static const char* const kSoundFileName[kSoundID_Num] =
	{
		"data/sound/shot.mp3",	// kSoundID_Shot,
		"data/sound/hit.mp3",	// kSoundID_Hit,
	};

	static int soundHandle[kSoundID_Num];

	void Load()
	{
		for (int i = 0; i < kSoundID_Num; i++)
		{
			soundHandle[i] = LoadSoundMem(kSoundFileName[i]);
		}
	}

	void Unload()
	{
		for (int i = 0; i < kSoundID_Num; i++)
		{
			DeleteSoundMem(soundHandle[i]);
		}
	}

	void PlaySound(SoundID id)
	{
		PlaySoundMem(soundHandle[id], DX_PLAYTYPE_BACK, TRUE);
	}
};
