#include "Game.h"
#include "SceneTitle.h"

void SceneTitle::init()
{
	m_endWait = -1;
}

SceneBase* SceneTitle::update()
{
	if (m_endWait >= 0)
	{
		m_endWait++;

		// �t�F�[�h�A�E�g���ďI��
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


	// �V�[���؂�ւ��e�X�g
	if (Pad::isTrigger(PAD_INPUT_1))
	{
	//	return (new SceneMain);
		m_endWait = 256;
	}
	return this;
}

void SceneTitle::draw()
{
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);

	DrawStringCenter(Game::cScreenHeight / 2 - 80, "�j���W���ł����[��");

	DrawStringCenter(Game::cScreenHeight / 2 + 80, "Z�L�[�������Ă�������");

	DrawBox(0, Game::cScreenHeight-48, Game::cScreenWidth, Game::cScreenHeight,
		GetColor(255, 0, 0), true);
	DrawStringCenter(Game::cScreenHeight - 32, "�[�@�����͂�P�O�O�˂���߂��J���ā@�[");
}

void SceneTitle::DrawStringCenter(int y, const char* str)
{
	int width = GetDrawFormatStringWidth(str);
	DrawString(Game::cScreenWidth / 2 - width/2, y, str, GetColor(255, 255, 255));
}
