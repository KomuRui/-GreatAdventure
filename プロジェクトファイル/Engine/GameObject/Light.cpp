#include "Light.h"
#include "../ResourceManager/Global.h"

//定数
namespace
{
	const XMFLOAT4 LIGHT_ATTENUATION = { 1.0f, ZERO, 0.2f, ZERO };       //ライトの減衰
	const XMFLOAT4 LIGHT_DIR = { ZERO, -1.0f, ZERO, ZERO };              //ライトの向き
	const XMFLOAT4 LIGHT_INIT_POSITION = { 99999, 99999, 99999, 99999 }; //ライトのポジションの初期値(使わないときは99999にするため) 
	const int LIGHT_STAGE_START_NUM = 1;                                 //ステージのライトのスタート番号(０番はPlayerのライトを使うため1番からスタート)
	const int LIGHT_INTENSITY = 1;                                       //ライトの強さ
}

//変数
XMFLOAT4 _LightPos[LIGHT_TOTAL_NUM];        //ライトのPosition格納
XMFLOAT4 _LightPosition;	                //ライトのポジション
XMFLOAT4 _LightAttenuation;		            //ライトの減衰
XMFLOAT4 _direction;			            //ライトの向き
float    _LightIntensity[LIGHT_TOTAL_NUM];  //ライトの強さ格納
int      _intensity;			            //ライトの強さ
int      _LightNowNumber;                   //今のライトの格納番号  


//初期化（プロジェクション行列作成）
void Light::Initialize()
{
	//ライトのポジションすべて初期化
	for (int counter = 0; counter < LIGHT_TOTAL_NUM; counter++)
	{
		ARGUMENT_INITIALIZE(_LightPos[counter],LIGHT_INIT_POSITION);
		ARGUMENT_INITIALIZE(_LightIntensity[counter], LIGHT_INTENSITY);
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

//位置と強さを設定
int Light::CreateLight(XMFLOAT4 position, float intensity) { _LightPos[_LightNowNumber] = position; _LightIntensity[_LightNowNumber] = intensity; _LightNowNumber++; return _LightNowNumber - 1; }

//ライトの向きを設定
void Light::SetDirection(XMFLOAT4 direction) { _direction = direction; }

//ライトの強さを設定(Player用)
void Light::SetPlayerIntensity(float intensity) { _LightIntensity[0] = intensity; }

//ライトの強さ設定
void Light::SetIntensity(int num, float intensity) { _LightIntensity[num] = intensity; }

//ライト削除
void Light::DeleteLight(int num)
{
	//消したところより後ろすべて前に詰める
	for (int i = num; i < _LightNowNumber; i++)
	{
		ARGUMENT_INITIALIZE(_LightPos[i], _LightPos[i + 1]);
		ARGUMENT_INITIALIZE(_LightIntensity[i], _LightIntensity[i + 1]);
	}

	//一つ削除したので今のライトの格納番号も1引く
	_LightNowNumber--;

	//今のライトの格納番号の値をすべて初期化
	ARGUMENT_INITIALIZE(_LightPos[_LightNowNumber], LIGHT_INIT_POSITION);
	ARGUMENT_INITIALIZE(_LightIntensity[_LightNowNumber], LIGHT_INTENSITY);
};

//減衰パラメータを取得
XMFLOAT4 Light::GetAttenuation() { return _LightAttenuation; }

//位置を取得
XMFLOAT4 Light::GetPosition(int num) { return _LightPos[num]; }

//ライトの向きを取得
XMFLOAT4 Light::GetDirection() { return _direction; }

//ライトの強さを取得
float  Light::GetIntensity(int num) { return _LightIntensity[num]; }
