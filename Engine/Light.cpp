#include "Light.h"
#include "Global.h"
#include <map>

//定数
const XMFLOAT4 LIGHT_ATTENUATION = { 1, 0, 0.2, 0 };                 //ライトの減衰
const XMFLOAT4 LIGHT_DIR = { 0, -1, 0, 0 };                          //ライトの向き
const XMFLOAT4 LIGHT_INIT_POSITION = { 99999, 99999, 99999, 99999 }; //ライトのポジションの初期値(使わないときは99999にするため)
const int LIGHT_TOTAL_NUM = 8;                                       //ライトの総数          
const int LIGHT_STAGE_START_NUM = 1;                                 //ステージのライトのスタート番号(０番はPlayerのライトを使うため1番からスタート)
const int LIGHT_INTENSITY = 1;                                       //ライトの強さ

//変数
XMFLOAT4 _LightPos[LIGHT_TOTAL_NUM];  //ライトのPosition格納
XMFLOAT4 _LightPosition;	          //ライトのポジション
XMFLOAT4 _LightAttenuation;		      //ライトの減衰
XMFLOAT4 _direction;			      //ライトの向き
int      _intensity;			      //ライトの強さ
int      _LightNowNumber;             //今のライトの格納番号    

//初期化（プロジェクション行列作成）
void Light::Initialize()
{
	//ライトのポジションすべて初期化
	for (int counter = 0; counter < LIGHT_TOTAL_NUM; counter++)
	{
		ARGUMENT_INITIALIZE(_LightPos[counter],LIGHT_INIT_POSITION);
	}

	//各変数の初期化
	ARGUMENT_INITIALIZE(_LightNowNumber,LIGHT_STAGE_START_NUM);     //ライトの格納番号の初期化
	ARGUMENT_INITIALIZE(_LightPosition,LIGHT_INIT_POSITION);        //ライトの位置
	ARGUMENT_INITIALIZE(_LightAttenuation,LIGHT_ATTENUATION);	    //ライトの減衰パラメータ
	ARGUMENT_INITIALIZE(_direction,LIGHT_DIR);                      //ライトの向き
	ARGUMENT_INITIALIZE(_intensity,LIGHT_INTENSITY);                //ライトの強さ
}

//距離によってどのように明るさを変化させるか(減衰パラメータ)を設定
void Light::SetAttenuation(XMFLOAT4 attenuation) { _LightAttenuation = attenuation; }

//PlayerLightの位置を設定
void Light::SetPlayerPosition(XMFLOAT4 position) { _LightPos[0] = position; }

//位置を設定
void Light::SetPosition(XMFLOAT4 position) { _LightPos[_LightNowNumber] = position; _LightNowNumber++; }

//ライトの向きを設定
void Light::SetDirection(XMFLOAT4 direction) { _direction = direction; }

//ライトの強さを設定
void Light::SetIntensity(int intensity) { _intensity = intensity; }

//減衰パラメータを取得
XMFLOAT4 Light::GetAttenuation() { return _LightAttenuation; }

//位置を取得
XMFLOAT4 Light::GetPosition(int num) { return _LightPos[num]; }

//ライトの向きを取得
XMFLOAT4 Light::GetDirection() { return _direction; }

//ライトの強さを取得
int  Light::GetIntensity() { return _intensity; }
