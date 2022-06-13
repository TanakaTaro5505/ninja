#include <DxLib.h>
#include "assert.h"

//マクロが実際に動く時の中身の関数。こちらではなくassertDxを使う
void AssertDx(bool assert_bool, std::string assert_tex, std::string file, int line, std::string func) 
{
    if (assert_bool == false) 
    {
        //意図しない動作をしている旨を表示
        MessageBox(NULL, (
            "Assertion failed: \"" + assert_tex +
            "\",\n File:" + file
            + ",\n Line:" + std::to_string(line)
            + ",\n In Function:" + func
            ).c_str()
            , "Assertion failed", MB_OK | MB_ICONSTOP);

        DxLib_End();// ＤＸライブラリ使用の終了処理
        exit(-1);//-1を渡して終了する。
    }
}


//マクロが実際に動く時の中身の関数。こちらではなくassertDxを使う
void AssertDx(bool assert_bool, std::string assert_tex, std::string file, int line, std::string func, std::string info) 
{
    if (assert_bool == false) 
    {
        //意図しない動作をしている旨を表示
        MessageBox(NULL, (
            "Assertion failed: \"" + assert_tex +
            "\",\n File:" + file
            + ",\n Line:" + std::to_string(line)
            + ",\n In Function:" + func
            + ",\n Infomation:" + info
            ).c_str()
            , "Assertion failed", MB_OK | MB_ICONSTOP);

        DxLib_End();// ＤＸライブラリ使用の終了処理
        exit(-1);//-1を渡して終了する。
    }
}
