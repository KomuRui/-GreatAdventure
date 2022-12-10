#pragma once
#include "Direct3D.h"

//安全にメモリを開放するためのマクロ
#define SAFE_DELETE(p) {if ((p)!=nullptr) { delete (p); (p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if ((p)!=nullptr) { delete[] (p); (p)=nullptr;}}
#define SAFE_RELEASE(p) {if ((p)!=nullptr) { p->Release(); (p)=nullptr;}}

//////角度

//0度
#define ZEROPI_DEGREES  0

//360度
#define TWOPI_DEGREES  360

//////初期化

//0に初期化
#define ZERO_INITIALIZE(p) { p = 0;}

//1に初期化
#define ONE_INITIALIZE(p) { p = 1;}

//引数で初期化
#define ARGUMENT_INITIALIZE(p,t){ p = t;}

//////定数

//0なら
#define ZERO 0

//////関数

//iniファイルからfloat型の変数を取ってくる
static float GetPrivateProfilefloat(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpDefault,LPCTSTR lpFileName)
{
	char caption[64];
	int len = GetPrivateProfileString(lpAppName, lpKeyName, lpDefault, caption, 64, lpFileName);

	//情報が取れているなら
	if (len)
		return strtof(caption, NULL);   //取った情報を返す
	else
		return strtof(lpDefault, NULL); //Defaultの情報を返す
}