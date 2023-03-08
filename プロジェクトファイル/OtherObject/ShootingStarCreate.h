#pragma once
#include "../Engine/GameObject/GameObject.h"

//海のモデル
class ShootingStarCreate : public GameObject
{
	int hTime_; //タイマーのハンドル

public:

	//コンストラクタ
	ShootingStarCreate(GameObject* parent);

	/////////////////////オーバーライドする関数//////////////////////

	//初期化
	void Initialize() override;

	//更新の前に一回呼ばれる関数
	void StartUpdate() override {};

	//更新
	void Update() override;

	//描画
	void Draw() override {};

	//開放
	void Release() override {};

	///////////////////////////関数//////////////////////////////

	/// <summary>
	/// 生成
	/// </summary>
	void Generation();
};

