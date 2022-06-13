#pragma once
#include "DxLib.h"
#include "PadUtil.h"

// �R�}���h�I��
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
	// �\����Ԃŏ������~�߂�	�J�[�\���\����Ԃɂ��邾��
	void pause();

	void update();
	void draw();

	void incSelect();
	void decSelect();
	int getSelectIndex() const { return m_selectNo; }

	bool isLoaded() { return m_isLoad; }
	// �㉺���[�v	�f�t�H���g��true
	void setLoop(bool isLoop) { m_isLoop = isLoop; }
	// �w�i�E�C���h�E�\��	�f�t�H���g��true
	void setDispWindow(bool isDisp) { m_isDispWindow = isDisp; }
private:
	// ���݂̑I�����̓��e����E�C���h�E�T�C�Y�����肷��
	void calcWindowSize();
private:
	bool m_isLoad;
	
	const char* m_commandTitle;

	// �I�������
	int m_commandNum;
	CommandData m_commandData[cCommandMax];

	// �I��
	int m_selectNo;
	int m_frameCount;

	// �㉺�I�����̃��[�v
	bool m_isLoop;
	// �w�i�E�C���h�E�\��
	bool m_isDispWindow;
	int m_windowLeft;
	int m_windowTop;
	int m_windowRight;
	int m_windowBottom;
};
