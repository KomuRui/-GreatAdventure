#pragma once
#include "GameObject.h"

//-----------------------------------------------------------
//カメラ
//-----------------------------------------------------------
namespace Camera
{
	//初期化（プロジェクション行列作成）
	void Initialize();

	//更新（ビュー行列作成）
	void Update();

	//カメラの振動
	XMFLOAT3 Vibration();

	//視点（カメラの位置）を設定
	void SetPosition(const XMFLOAT3& position);

	//焦点（見る位置）を設定
	void SetTarget(const XMFLOAT3& target);

	//上方向のベクトルを設定
	void SetUpDirection(XMVECTOR direction);

	//画角を設定
	void SetFieldAngle(int angle);

	//カメラ振動を設定
	//引数 : 振動の強さ
	void SetCameraVibration(float strength, float attenuation = 0.01f);

	//位置を取得
	XMFLOAT3 GetPosition();

	//焦点を取得
	XMFLOAT3 GetTarget();

	//ビュー行列を取得
	XMMATRIX GetViewMatrix();

	//プロジェクション行列を取得
	XMMATRIX GetProjectionMatrix();

	//ビルボード用回転行列を取得
	XMMATRIX GetBillboardMatrix();
};