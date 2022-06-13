#include <DxLib.h>
#include "assert.h"

//�}�N�������ۂɓ������̒��g�̊֐��B������ł͂Ȃ�assertDx���g��
void AssertDx(bool assert_bool, std::string assert_tex, std::string file, int line, std::string func) 
{
    if (assert_bool == false) 
    {
        //�Ӑ}���Ȃ���������Ă���|��\��
        MessageBox(NULL, (
            "Assertion failed: \"" + assert_tex +
            "\",\n File:" + file
            + ",\n Line:" + std::to_string(line)
            + ",\n In Function:" + func
            ).c_str()
            , "Assertion failed", MB_OK | MB_ICONSTOP);

        DxLib_End();// �c�w���C�u�����g�p�̏I������
        exit(-1);//-1��n���ďI������B
    }
}


//�}�N�������ۂɓ������̒��g�̊֐��B������ł͂Ȃ�assertDx���g��
void AssertDx(bool assert_bool, std::string assert_tex, std::string file, int line, std::string func, std::string info) 
{
    if (assert_bool == false) 
    {
        //�Ӑ}���Ȃ���������Ă���|��\��
        MessageBox(NULL, (
            "Assertion failed: \"" + assert_tex +
            "\",\n File:" + file
            + ",\n Line:" + std::to_string(line)
            + ",\n In Function:" + func
            + ",\n Infomation:" + info
            ).c_str()
            , "Assertion failed", MB_OK | MB_ICONSTOP);

        DxLib_End();// �c�w���C�u�����g�p�̏I������
        exit(-1);//-1��n���ďI������B
    }
}
