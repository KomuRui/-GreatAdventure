#include "Light.h"

XMFLOAT4 _position;
XMFLOAT4 _attenuation;
XMFLOAT4 _direction;

//初期化（プロジェクション行列作成）
void Light::Initialize()
{
	_position = XMFLOAT4(0, 50, -50, 0);     //ライトの位置
	_attenuation = XMFLOAT4(1, 0, 0.2, 0);	 //カメラの焦点
	_direction = XMFLOAT4(0, -1, 0, 0);
}

//距離によってどのように明るさを変化させるか(減衰パラメータ)を設定
void Light::SetAttenuation(XMFLOAT4 attenuation) { _attenuation = attenuation; }

//位置を設定
void Light::SetPosition(XMFLOAT4 position) { _position = position; }

//ライトの向きを設定
void Light::SetDirection(XMFLOAT4 direction) { _direction = direction; }

//減衰パラメータを取得
XMFLOAT4 Light::GetAttenuation() { return _attenuation; }

//位置を取得
XMFLOAT4 Light::GetPosition() { return _position; }

//位置を取得
XMFLOAT4 Light::GetDirection() { return _direction; }
