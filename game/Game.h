#pragma once

// �Q�[���S�ʂŎg�p�����`
namespace Game
{
// define ---------------------------------------------
	// �E�C���h�E���[�h�ݒ�
#ifdef _DEBUG
	static constexpr bool cIsWindowMode = true;
#else
	static constexpr bool cIsWindowMode = false;
#endif

	// �E�C���h�E�^�C�g��
	static const char* const cWindowTitle = "�j���W���ł����[��";

	// �X�N���[���T�C�Y
#if false
	// 4:3
	static constexpr int cScreenWidth = 640;
	static constexpr int cScreenHeight = 480;
#endif
#if true
	// 16:9
	static constexpr int cScreenWidth = 960;
	static constexpr int cScreenHeight = 540;
#endif
	// �t�F�[�h�C���A�E�g���x	�t�F�[�h���Ԃ�	255/���x�t���[��
	static constexpr int cFadeSpeedNormal = 16;
};
