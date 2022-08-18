#include "DxLib.h"

#include "Game.h"
#include "SceneManager.h"
#include "Ui.h"
#include "Sound.h"

#include "title/SceneTitle.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	// Windows���[�h�ɂ���
	ChangeWindowMode(Game::cIsWindowMode);
	SetMainWindowText(Game::cWindowTitle);
	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(Game::cScreenWidth, Game::cScreenHeight, 32);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// �O���t�B�b�N�ǂݍ���
	UI::LoadGraphic();
	// �T�E���h�ǂݍ���
	Sound::Load();

	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);

	// �w�i�F�̐ݒ�
	SetBackgroundColor(0, 0, 0);

	SceneManager scene;
	scene.change(new SceneTitle);

	bool isFrameFeed = false;
	int time = 0;
	while (ProcessMessage() == 0)
	{
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

	//	int time = GetNowCount();
		LONGLONG  time = GetNowHiPerformanceCount();
		//����ʏ���
		ClearDrawScreen();

		// �e�V�[���̏���
		scene.update();
		scene.draw();

		//����ʂ�\��ʂ����ւ���
		ScreenFlip();
		// �t���[�����[�g�Œ�

		if (isFrameFeed)
		{
			// �R�}���胂�[�h
			while (!Pad::isTrigger(PAD_INPUT_7))
			{
				Pad::update();
				if (Pad::isTrigger(PAD_INPUT_8))
				{
					isFrameFeed = false;
					break;
				}
			}
		}
		else
		{
		//	while (GetNowCount() - time < 17)
			while (GetNowHiPerformanceCount() - time < 16667)
			{
			}
			if (Pad::isTrigger(PAD_INPUT_7))
			{
				isFrameFeed = true;
			}
		}
	}

	// �O���t�B�b�N�I��
	UI::UnloadGraphic();
	// �T�E���h�I��
	Sound::Unload();

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}
