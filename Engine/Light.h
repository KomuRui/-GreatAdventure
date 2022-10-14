#pragma once
#include "GameObject.h"

//-----------------------------------------------------------
//点光源カメラ
//-----------------------------------------------------------
namespace Light
{
	//初期化（ライトのPosと向き）
	void Initialize();

	//ライトの位置を設定
	void SetPosition(XMFLOAT4 position);

	//距離によってどのように明るさを変化させるか(減衰パラメータ)を設定
	void SetAttenuation(XMFLOAT4 attenuation);

	//位置を取得
	XMFLOAT4 GetPosition();

	//減衰パラメータを取得
	XMFLOAT4 GetAttenuation();

	//減衰パラメータを取得
	XMFLOAT4 GetDirection();
};

