#include "Ui.h"
#include "DxLib.h"

namespace UI
{
	// ƒEƒCƒ“ƒhƒE‹«ŠE
	static const int cBorderChipWH = 8;

	static const char* const cBorderFileName = "data/graphic/border.png";
	static int m_hBorder[9];

	void LoadGraphic()
	{
#if false
		LoadDivGraph(cBorderFileName, 9, 3, 3,
			cBorderChipWH, cBorderChipWH, m_hBorder);
#endif
	}
	void UnloadGraphic()
	{
#if false
		for( int i = 0; i < 9; i++ )
		{
			DeleteGraph(m_hBorder[i]);
		}
#endif
	}

	void DrawWindow(int left, int top, int right, int bottom)
	{
#if true
		// ƒvƒƒOƒ‰ƒ€‚É‚æ‚é•`‰æ
		DrawBox(left, top, right, bottom,
			GetColor(0, 0, 0), true);
		// ü‚Ì‘¾‚³•ªŽlŠp‚ð•`‰æ
		for (int i = 0; i < cWindowBirderWidth; i++)
		{
			DrawBox(left + i, top + i, right - i, bottom - i,
				GetColor(255, 255, 255), false);
		}
#endif
#if false
		// Žl‹÷
		DrawGraph(left                 , top, m_hBorder[0], true);
		DrawGraph(right - cBorderChipWH, top, m_hBorder[2], true);
		DrawGraph(left                 , bottom - cBorderChipWH, m_hBorder[6], true);
		DrawGraph(right - cBorderChipWH, bottom - cBorderChipWH, m_hBorder[8], true);

		// ã‹«ŠE
		DrawExtendGraph(left + cBorderChipWH, top, right - cBorderChipWH, top+cBorderChipWH,
			m_hBorder[1], true);
		// ¶‹«ŠE
		DrawExtendGraph(left, top + cBorderChipWH, left + cBorderChipWH, bottom - cBorderChipWH,
			m_hBorder[3], true);
		// ‰E‹«ŠE
		DrawExtendGraph(right - cBorderChipWH, top + cBorderChipWH, right, bottom - cBorderChipWH,
			m_hBorder[5], true);
		// ‰º‹«ŠE
		DrawExtendGraph(left + cBorderChipWH, bottom - cBorderChipWH, right - cBorderChipWH, bottom,
			m_hBorder[7], true);
		
		// •¶Žš—Ìˆæ
		DrawExtendGraph(left + cBorderChipWH, top + cBorderChipWH, right - cBorderChipWH, bottom - cBorderChipWH,
			m_hBorder[4], true);
#endif
	}
};
