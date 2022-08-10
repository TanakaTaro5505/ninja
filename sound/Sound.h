#pragma once

#include "DxLib.h"

namespace Sound
{
	typedef enum SoundID
	{
		// bgm
		kSoundID_BgmPlay,

		// �^�C�g�����
		kSoundID_Start,
		// ���C��
		kSoundID_Shot,
		kSoundID_Hit,
		kSoundID_Dead,
		kSoundID_Levelup,
		kSoundID_EnemyDead,
		kSoundID_BossAttack,
		kSoundID_BossDead,

		kSoundID_Num
	}SoundID;

	// �T�E���h�̃��[�h�A�A�����[�h
	void Load();
	void Unload();
	
	// BGM�炷(���[�v�Đ�)
	void PlayBgm(SoundID id);
	void StopBgm(SoundID id);

	// ���ʉ��炷
	void PlaySound(SoundID id);
};