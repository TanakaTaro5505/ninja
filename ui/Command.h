#pragma once
#include "DxLib.h"
#include "PadUtil.h"

// コマンド選択
class Command
{
private:
	typedef struct
	{
		const char* text;
		int x;
		int y;
	}CommandData;
public:
	static const int cCommandMax = 16;
public:
	Command();
	virtual ~Command() {}

	void start( const char* openSundFileName = nullptr );
	void setCommandTitle(const char* titleText);
	void addCommand( const char* commandText, int x, int y );
	void end();
	// 表示状態で処理を止める	カーソル表示状態にするだけ
	void pause();

	void update();
	void draw();

	void incSelect();
	void decSelect();
	int getSelectIndex() const { return m_selectNo; }

	bool isLoaded() { return m_isLoad; }
	// 上下ループ	デフォルトはtrue
	void setLoop(bool isLoop) { m_isLoop = isLoop; }
	// 背景ウインドウ表示	デフォルトはtrue
	void setDispWindow(bool isDisp) { m_isDispWindow = isDisp; }
private:
	// 現在の選択肢の内容からウインドウサイズを決定する
	void calcWindowSize();
private:
	bool m_isLoad;
	
	const char* m_commandTitle;

	// 選択肢情報
	int m_commandNum;
	CommandData m_commandData[cCommandMax];

	// 選択
	int m_selectNo;
	int m_frameCount;

	// 上下選択肢のループ
	bool m_isLoop;
	// 背景ウインドウ表示
	bool m_isDispWindow;
	int m_windowLeft;
	int m_windowTop;
	int m_windowRight;
	int m_windowBottom;
};
