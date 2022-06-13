#pragma once

// �Q�[���S�ʂŎg�p�����`
namespace Game
{
// define ---------------------------------------------
	// �E�C���h�E���[�h�ݒ�
#ifdef _DEBUG
	static const bool cIsWindowMode = true;
#else
	static const bool cIsWindowMode = false;
#endif

	// �E�C���h�E�^�C�g��
	static const char* const cWindowTitle = "TEMPLATE";

	// �X�N���[���T�C�Y
#if false
	// 4:3
	static const int cScreenWidth = 640;
	static const int cScreenHeight = 480;
#endif
#if true
	// 16:9
	static const int cScreenWidth = 960;
	static const int cScreenHeight = 540;
#endif
	// �t�F�[�h�C���A�E�g���x	�t�F�[�h���Ԃ�	255/���x�t���[��
	static const int cFadeSpeedNormal = 16;
};
