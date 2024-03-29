#include "Game.h"
#include "Sound.h"
#include "SceneTitle.h"

void SceneTitle::init()
{
	m_endWait = -1;
	m_titleGraphic = LoadGraph("data/logo/title.png");
}

void SceneTitle::deleteGraph()
{
	DeleteGraph(m_titleGraphic);
}

SceneBase* SceneTitle::update()
{
	if (m_endWait >= 0)
	{
		m_endWait++;

		// フェードアウトして終了
		m_fadeBright -= Game::cFadeSpeedNormal;
		if (m_fadeBright <= 0)
		{
			m_fadeBright = 0;
			return (new SceneMain);
		}
		return this;
	}

	m_fadeBright += Game::cFadeSpeedNormal;
	if (m_fadeBright >= 255)	m_fadeBright = 255;


	// シーン切り替えテスト
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		Sound::PlaySound(Sound::kSoundID_Start);
	//	return (new SceneMain);
		m_endWait = 256;
	}
	return this;
}

void SceneTitle::draw()
{
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);

//	DrawStringCenter(Game::cScreenHeight / 2 - 80, "ニンジャでござーる");
	int sizeX, sizeY;
	GetGraphSize(m_titleGraphic, &sizeX, &sizeY);
	DrawGraph((Game::cScreenWidth - sizeX) / 2, (Game::cScreenHeight - sizeY) / 2-80, m_titleGraphic, 1);

	DrawStringCenter(Game::cScreenHeight / 2 + 80, "Zキーを押してください");

	DrawBox(0, Game::cScreenHeight-48, Game::cScreenWidth, Game::cScreenHeight,
		GetColor(255, 0, 0), true);
	DrawStringCenter(Game::cScreenHeight - 32, "ー　おおはら１００ねんをめさ゛して　ー");
}

void SceneTitle::DrawStringCenter(int y, const char* str)
{
	int width = GetDrawFormatStringWidth(str);
	DrawString(Game::cScreenWidth / 2 - width/2, y, str, GetColor(255, 255, 255));
}
