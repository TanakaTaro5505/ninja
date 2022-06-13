#include "Command.h"
#include "Game.h"
#include "Ui.h"

// カーソル点滅
static const int cBlinkIntervel = 30;
static const int cBlinkDisp = 20;

// ===================================================================================
Command::Command()
{
	m_isLoad = false;

	m_commandTitle = nullptr;

	m_commandNum = 0;
	for (int i = 0; i < cCommandMax; i++)
	{
		m_commandData[i].text = nullptr;
		m_commandData[i].x = 0;
		m_commandData[i].y = 0;
	}
	m_selectNo = 0;
	m_frameCount = 0;

	m_isLoop = true;

	m_isDispWindow = false;
}

void Command::start(const char* openSundFileName)
{
	m_isLoad = true;

	m_commandTitle = nullptr;

	m_commandNum = 0;
	for (int i = 0; i < cCommandMax; i++)
	{
		m_commandData[i].text = nullptr;
		m_commandData[i].x = 0;
		m_commandData[i].y = 0;
	}
	m_selectNo = 0;
	m_frameCount = 0;

	m_isLoop = true;

	m_isDispWindow = false;

	if (openSundFileName != nullptr)
	{
		PlaySoundFile(openSundFileName, DX_PLAYTYPE_BACK);
	}
	else
	{
		PlaySoundFile("data/sound/cancel1.wav", DX_PLAYTYPE_BACK);
	}
}

void Command::setCommandTitle(const char* titleText)
{
	m_commandTitle = titleText;
}

void Command::addCommand(const char* commandText, int x, int y)
{
	if (m_commandNum >= cCommandMax)	return;

	m_commandData[m_commandNum].text = commandText;
	m_commandData[m_commandNum].x = x;
	m_commandData[m_commandNum].y = y;
	m_commandNum++;

	calcWindowSize();
}

void Command::end()
{
	if (!m_isLoad)	return;

	m_isLoad = false;
	PlaySoundFile("data/sound/cancel1.wav", DX_PLAYTYPE_BACK);
}

void Command::pause()
{
	m_frameCount = 0;	// カーソル表示状態にするだけ
}

void Command::update()
{
	m_frameCount++;
	if (m_frameCount > cBlinkIntervel)	m_frameCount = 0;

	if (Pad::isTrigger(PAD_INPUT_DOWN))
	{
		incSelect();
		PlaySoundFile("data/sound/cursor2.wav", DX_PLAYTYPE_BACK);
	}
	if (Pad::isTrigger(PAD_INPUT_UP))
	{
		decSelect();
		PlaySoundFile("data/sound/cursor2.wav", DX_PLAYTYPE_BACK);
	}
}

void Command::draw()
{
	if (!m_isLoad)	return;

	if (m_isDispWindow)
	{
		UI::DrawWindow(m_windowLeft, m_windowTop, m_windowRight, m_windowBottom);
	}

	for (int i = 0; i < m_commandNum; i++)
	{
		if( (i == m_selectNo) &&(m_frameCount < cBlinkDisp) )
		{
			DrawString(m_commandData[i].x-16, m_commandData[i].y, "＞", GetColor(255, 255, 255));
		}
		DrawString(m_commandData[i].x, m_commandData[i].y, m_commandData[i].text, GetColor(255, 255, 255));
	}
	if (m_isDispWindow)
	{
		if (m_commandTitle)
		{
			int titleWidth = GetDrawFormatStringWidth(m_commandTitle);
			int windowWidth = m_windowRight - m_windowLeft;
			int offset = windowWidth - titleWidth;
			DrawBox(m_windowLeft + offset / 2, m_windowTop, m_windowRight - offset / 2, m_windowTop+16,GetColor(0,0,0), true);
			DrawString(m_windowLeft + offset/2, m_windowTop-16, m_commandTitle, GetColor(255, 255, 255));
		}
	}
}

void Command::incSelect()
{
	m_selectNo++;
	if(m_selectNo >= m_commandNum)
	{ 
		if (m_isLoop)
		{
			m_selectNo = 0;
		}
		else
		{
			m_selectNo = m_commandNum-1;
		}
	}
}
void Command::decSelect()
{
	m_selectNo--;
	if (m_selectNo < 0)
	{
		if (m_isLoop)
		{
			m_selectNo = m_commandNum - 1;
		}
		else
		{
			m_selectNo = 0;
		}
	}
}

void Command::calcWindowSize()
{
	int tempLeft = Game::cScreenWidth;
	int tempTop = Game::cScreenHeight;
	int tempRight = 0;
	int tempBottom = 0;

	for (int i = 0; i < m_commandNum; i++)
	{
		if (tempLeft > m_commandData[i].x - 16 - 16)
		{
			tempLeft = m_commandData[i].x - 16 - 16;
		}
		if (tempTop > m_commandData[i].y - 16)
		{
			tempTop = m_commandData[i].y - 16;
		}
		int width = GetDrawFormatStringWidth(m_commandData[i].text);
		if (tempRight < m_commandData[i].x + width + 32)
		{
			tempRight = m_commandData[i].x + width + 32;
		}
		if (tempBottom < m_commandData[i].y + 32 + 16)
		{
			tempBottom = m_commandData[i].y + 32 + 16;
		}
	}
	m_windowLeft = tempLeft;
	m_windowTop = tempTop;
	m_windowRight = tempRight;
	m_windowBottom = tempBottom;
}