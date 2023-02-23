#pragma once
#include "../ResourceManager/Model.h"

/// <summary>
/// どんな地形でも正しい姿勢を取ってくれるコンポーネント(3Dモデル)
/// 地形のモデル番号が必要
/// 重力が適応してあり,真下の当たり判定だけしている
/// </summary>
class Posture
{
public:

	Transform* transform_; //モデルのトランスフォーム
	XMVECTOR* down_;       //キャラの下ベクトル
	XMVECTOR* vNormal_;    //現在の真下の法線
	int hGroundModel_;     //ステージのモデル番号

	//コンストラクタ
	Posture();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 真下の法線を調べてキャラの上軸を決定する
	/// </summary>
	/// <param name="data">当たり判定に必要なデータ</param>
	void CheckUnderNormal(const RayCastData& data);

	/// <summary>
	/// レイで当たり判定(3D用)
	/// </summary>
	/// <param name="data">当たり判定に必要なデータ</param>
	void StageRayCast(const RayCastData& data);
};

