#pragma once
#include <string>

//
//assert
//

//assertionマクロ。こっちをつかう。
//意図していない部分や、ファイル名、何行目か等の情報が得られる。
#define assertDx(assertion) AssertDx(assertion,#assertion,__FILE__,__LINE__,__FUNCTION__)

//assertionマクロ。こっちをつかう。
//意図していない部分や、ファイル名、何行目か等の情報が得られる。
//デバッグ用に情報(std::string)を1つ埋め込める
#define assertDxInfo(assertion,info) AssertDx(assertion,#assertion,__FILE__,__LINE__,__FUNCTION__,info)


//マクロが実際に動く時の中身の関数。こちらではなくassertDxを使う
void AssertDx(bool assert_bool, std::string assert_tex, std::string file, int line, std::string func);

//マクロが実際に動く時の中身の関数。こちらではなくassertDxを使う
//デバッグ用に情報を1つ埋め込める
void AssertDx(bool assert_bool, std::string assert_tex, std::string file, int line, std::string func, std::string info);
