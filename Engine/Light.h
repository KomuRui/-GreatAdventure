#pragma once
#include "GameObject.h"

//定数
const int LIGHT_TOTAL_NUM = 8; //ライトの総数        

//-----------------------------------------------------------
//点光源ライト
//-----------------------------------------------------------
namespace Light
{
	//初期化（ライトのPosと向き）
	void Initialize();

	//ライトの位置を設定
	void SetPlayerPosition(XMFLOAT4 position);

	//位置を設定
	void SetPositionAndIntensity(XMFLOAT4 position, float intensity);

	//距離によってどのように明るさを変化させるか(減衰パラメータ)を設定
	void SetAttenuation(XMFLOAT4 attenuation);

	//ライトの向きを設定
	void SetDirection(XMFLOAT4 direction);

	//ライトの強さを設定
	void SetIntensity(float intensity);

	//位置を取得
	XMFLOAT4 GetPosition(int num);

	//減衰パラメータを取得
	XMFLOAT4 GetAttenuation();

	//ライトの向き
	XMFLOAT4 GetDirection();

	//ライトの強さ
	float  GetIntensity(int num);
};

