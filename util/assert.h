#pragma once
#include <string>

//
//assert
//

//assertion�}�N���B�������������B
//�Ӑ}���Ă��Ȃ�������A�t�@�C�����A���s�ڂ����̏�񂪓�����B
#define assertDx(assertion) AssertDx(assertion,#assertion,__FILE__,__LINE__,__FUNCTION__)

//assertion�}�N���B�������������B
//�Ӑ}���Ă��Ȃ�������A�t�@�C�����A���s�ڂ����̏�񂪓�����B
//�f�o�b�O�p�ɏ��(std::string)��1���ߍ��߂�
#define assertDxInfo(assertion,info) AssertDx(assertion,#assertion,__FILE__,__LINE__,__FUNCTION__,info)


//�}�N�������ۂɓ������̒��g�̊֐��B������ł͂Ȃ�assertDx���g��
void AssertDx(bool assert_bool, std::string assert_tex, std::string file, int line, std::string func);

//�}�N�������ۂɓ������̒��g�̊֐��B������ł͂Ȃ�assertDx���g��
//�f�o�b�O�p�ɏ���1���ߍ��߂�
void AssertDx(bool assert_bool, std::string assert_tex, std::string file, int line, std::string func, std::string info);
