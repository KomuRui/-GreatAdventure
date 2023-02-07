#pragma once
#include "../../Engine/GameObject.h"
#include "../../Engine/Time.h"

//前定義
class CreateStage;

/// <summary>
/// ユーザがゲームスタートする時のUI
/// </summary>
class UserGameStartUI : public GameObject
{
	//UIとか表示する用
	CreateStage* pCreateStage_;

public:

	//コンストラクタ
	UserGameStartUI(GameObject* parent);

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
};

