#include "Light.h"
#include <map>

std::map<std::string,XMFLOAT4> LightPos;       //ライトごとのPosition格納(格納するときは名前とポジション設定)
std::map<std::string,XMFLOAT4> LightIntensity; //ライトごとの強さ格納(格納するときは名前とポジション設定)
XMFLOAT4 _position;					           //ライトのポジション
XMFLOAT4 _attenuation;				      	   //ライトの減衰
XMFLOAT4 _direction;						   //ライトの向き
int      _intensity;						   //ライトの強さ

//初期化（プロジェクション行列作成）
void Light::Initialize()
{
	_position = XMFLOAT4(0, 50, -50, 0);     //ライトの位置
	_attenuation = XMFLOAT4(1, 0, 0.2, 0);	 //ライトの減衰パラメータ
	_direction = XMFLOAT4(0, -1, 0, 0);      //ライトの向き
	_intensity = 1;                          //ライトの強さ
}

//距離によってどのように明るさを変化させるか(減衰パラメータ)を設定
void Light::SetAttenuation(XMFLOAT4 attenuation) { _attenuation = attenuation; }

//位置を設定
void Light::SetPosition(XMFLOAT4 position) { _position = position; }

//ライトの向きを設定
void Light::SetDirection(XMFLOAT4 direction) { _direction = direction; }

//ライトの強さを設定
void Light::SetIntensity(int intensity) { _intensity = intensity; }

//減衰パラメータを取得
XMFLOAT4 Light::GetAttenuation() { return _attenuation; }

//位置を取得
XMFLOAT4 Light::GetPosition() { return _position; }

//ライトの向きを取得
XMFLOAT4 Light::GetDirection() { return _direction; }

//ライトの強さを取得
int  Light::GetIntensity() { return _intensity; }
