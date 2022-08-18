#include "DxLib.h"

#include "Game.h"
#include "SceneManager.h"
#include "Ui.h"
#include "Sound.h"

#include "title/SceneTitle.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	// Windowsモードにする
	ChangeWindowMode(Game::cIsWindowMode);
	SetMainWindowText(Game::cWindowTitle);
	// 画面サイズの設定
	SetGraphMode(Game::cScreenWidth, Game::cScreenHeight, 32);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// グラフィック読み込み
	UI::LoadGraphic();
	// サウンド読み込み
	Sound::Load();

	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);

	// 背景色の設定
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
		//裏画面消す
		ClearDrawScreen();

		// 各シーンの処理
		scene.update();
		scene.draw();

		//裏画面を表画面を入れ替える
		ScreenFlip();
		// フレームレート固定

		if (isFrameFeed)
		{
			// コマ送りモード
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

	// グラフィック終了
	UI::UnloadGraphic();
	// サウンド終了
	Sound::Unload();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
