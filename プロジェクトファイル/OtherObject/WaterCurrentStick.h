#pragma once
#include "../Engine/GameObject/GameObject.h"

//水流を発生する棒の種類
enum class WaterCurrentStickType
{
	NORMAL,   //普通
	ROTATION, //回転
	MAX       //最大
};

//水流を発生する棒
class WaterCurrentStick : public GameObject
{
	int hModel_;   				  //モデル番号
	int hEffect_;				  //エフェクト番号
	WaterCurrentStickType type_;  //型
	std::string filePath_;		  //ファイルのパス
	XMVECTOR front_;			  //前ベクトル

public:

	//コンストラクタ
	WaterCurrentStick(GameObject* parent, std::string modelFilePath_, std::string name);

	/////////////////////オーバーライドする関数//////////////////////

	//初期化
	void Initialize() override;

	//更新の前に一回呼ばれる関数
	void StartUpdate() override {};

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	////////////////////////////関数////////////////////////////

	/// <summary>
	/// 通常
	/// </summary>
	void Normal(){};

	/// <summary>
	/// 回転
	/// </summary>
	void Rotation();

	/// <summary>
	/// 型を設定
	/// </summary>
	/// <param name="type">設定したい型</param>
	void SetType(WaterCurrentStickType type) { type_ = type; }
};

