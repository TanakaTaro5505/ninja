#pragma once

// ゲーム全般で使用する定義
namespace Game
{
// define ---------------------------------------------
	// ウインドウモード設定
#ifdef _DEBUG
	static constexpr bool cIsWindowMode = true;
#else
	static constexpr bool cIsWindowMode = false;
#endif

	// ウインドウタイトル
	static const char* const cWindowTitle = "ニンジャでござーる";

	// スクリーンサイズ
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
	// フェードインアウト速度	フェード時間は	255/速度フレーム
	static constexpr int cFadeSpeedNormal = 16;
};
