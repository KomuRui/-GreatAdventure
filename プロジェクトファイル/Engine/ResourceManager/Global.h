#pragma once
#include "../DirectX/Direct3D.h"
#include <sstream>
#include <iomanip>

using namespace std;

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
#define ZERO 0.0f

//上のベクトル
static const XMVECTOR UP_VECTOR = { 0,1,0,0 };

//下のベクトル
static const XMVECTOR DOWN_VECTOR = { 0,-1,0,0 };

//左のベクトル
static const XMVECTOR LEFT_VECTOR = { -1,0,0,0 };

//右のベクトル
static const XMVECTOR RIGHT_VECTOR = { 1,0,0,0 };

//前のベクトル
static const XMVECTOR STRAIGHT_VECTOR = { 0,0,1,0 };

//後ろのベクトル
static const XMVECTOR BACK_VECTOR = { 0,0,-1,0 };


//////関数

//XMFLOAT3同士を引き算してくれる(第一引数 - 第二引数)
static XMFLOAT3 SubTract(XMFLOAT3 a, XMFLOAT3 b)
{
	return XMFLOAT3(a.x - b.x, a.y - b.y, a.z - b.z);
}

//XMFLOAT3同士を足してくれる
static XMFLOAT3 Float3Add(XMFLOAT3 a, XMFLOAT3 b)
{
	return XMFLOAT3(a.x + b.x, a.y + b.y, a.z + b.z);
}

//距離を求めてくれる
static float RangeCalculation(XMFLOAT3 a, XMFLOAT3 b)
{
	XMFLOAT3 c = SubTract(a, b);

	return sqrtf((c.x * c.x) +
		         (c.y * c.y) +
		         (c.z * c.z));
}

//XMVECTORの変数をXMFLOAT3に変えて返してくれる
static XMFLOAT3 VectorToFloat3(XMVECTOR v)
{
	XMFLOAT3 a;
	XMStoreFloat3(&a, v);

	return a;
}

//距離を求めてくれる
static float RangeCalculation(XMVECTOR a, XMVECTOR b)
{
	return  RangeCalculation(VectorToFloat3(a), VectorToFloat3(b));
}

//ランダム(a以上b以下のランダムの値を出す)
static int Random(int a, int b)
{
	int num = (b - a) + 1;

	return (rand() % num) + a;
}

//ベクトルが0かどうか
static bool VectorNotZero(XMVECTOR a)
{
	return (XMVectorGetX(a) == 0 && XMVectorGetY(a) == 0 && XMVectorGetZ(a) == 0 && XMVectorGetW(a) == 0);
}

//二つベクトルの値が違うかどうか
static bool TwoVectorNotValue(XMVECTOR a, XMVECTOR b)
{
	return (XMVectorGetX(a) != XMVectorGetX(b) || XMVectorGetY(a) != XMVectorGetY(b) || XMVectorGetZ(a) != XMVectorGetZ(b));
}

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

//内積の結果をラジアン角で取得する
static float GetDotRadians(XMVECTOR a, XMVECTOR b)
{
	return acos(XMVectorGetX(XMVector3Dot(XMVector3Normalize(a), XMVector3Normalize(b))));
}

//ベクトルの長さ取得
static float VectorLen(const XMVECTOR& v)
{
	return XMVectorGetX(XMVector3Length(v));
}


/// <summary>
/// floatからstringに変換
/// </summary>
/// <param name="f">変換したい浮動小数点数</param>
/// <param name="digits">浮動小数点数の桁数</param>
/// <returns>変換した文字列</returns>
static std::string float_to_string(float f, int digits)
{
	ostringstream oss;

	oss << setprecision(digits) << setiosflags(ios::fixed) << f;

	return oss.str();

}

//ベクトルの小さい値を返す
static XMVECTOR MinVector(XMVECTOR a, XMVECTOR b)
{
	//距離求める
	float disA = RangeCalculation(XMVectorSet(ZERO,ZERO,ZERO,ZERO), a);
	float disB = RangeCalculation(XMVectorSet(ZERO,ZERO,ZERO,ZERO), b);

	if (disA <= disB)
		return a;
	else
		return b;
}

//ベクトルの大きい値を返す
static XMVECTOR MaxVector(XMVECTOR a, XMVECTOR b)
{
	//距離求める
	float disA = RangeCalculation(XMVectorSet(ZERO, ZERO, ZERO, ZERO), a);
	float disB = RangeCalculation(XMVectorSet(ZERO, ZERO, ZERO, ZERO), b);

	if (disA >= disB)
		return a;
	else
		return b;
}

////////////////////////////////////オペレーター////////////////////////////////////////////

static XMVECTOR operator*(const XMVECTOR& v, const XMMATRIX& m)
{
	return XMVector3TransformCoord(v, m);
}

static XMVECTOR operator*(const XMMATRIX& m,const XMVECTOR& v)
{
	return XMVector3TransformCoord(v, m);
}

static XMVECTOR operator-(const XMFLOAT3& a, const XMFLOAT3& b)
{
	return XMLoadFloat3(&a) - XMLoadFloat3(&b);
}

static XMVECTOR operator-(const XMFLOAT3& f3, const XMVECTOR& v)
{
	return XMLoadFloat3(&f3) - v;
}

static XMVECTOR operator-(const XMVECTOR& v,const XMFLOAT3& f3)
{
	return v - XMLoadFloat3(&f3);
}

static XMVECTOR operator+(const XMFLOAT3& a, const XMFLOAT3& b)
{
	return XMLoadFloat3(&a) + XMLoadFloat3(&b);
}

static XMVECTOR operator+(const XMFLOAT3& f3, const XMVECTOR& v)
{
	return XMLoadFloat3(&f3) + v;
}

static XMVECTOR operator+(const XMVECTOR& v, const XMFLOAT3& f3)
{
	return v + XMLoadFloat3(&f3);
}

static XMFLOAT3 operator*(const XMFLOAT3& f3, const float f)
{
	return XMFLOAT3(f3.x * f, f3.y * f, f3.z * f);
}

static XMFLOAT3 operator*(const float f, const XMFLOAT3& f3)
{
	return XMFLOAT3(f3.x * f, f3.y * f, f3.z * f);
}

static XMFLOAT3 operator/(const XMFLOAT3& f3, const float f)
{
	return XMFLOAT3(f3.x / f, f3.y / f, f3.z / f);
}
