#pragma once

// ゲーム全般で使用する定義
namespace Game
{
// define ---------------------------------------------
	// ウインドウモード設定
#ifdef _DEBUG
	static const bool cIsWindowMode = true;
#else
	static const bool cIsWindowMode = false;
#endif

	// ウインドウタイトル
	static const char* const cWindowTitle = "TEMPLATE";

	// スクリーンサイズ
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
	// フェードインアウト速度	フェード時間は	255/速度フレーム
	static const int cFadeSpeedNormal = 16;
};
