#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/ResourceManager/Time.h"
#include "../../Engine/ResourceManager/Text.h"

//前定義
class CreateStage;

/// <summary>
/// ユーザがゲームスタートする時のUI
/// </summary>
class UserGameStartUI : public GameObject
{
	//UIとか表示する用
	CreateStage* pCreateStage_;

	//画像
	int hCoinPict_;             //コイン画像
	int hStagePict_;            //ステージ画像
	int hCrossPict_;            //×画像

	//テキスト
	Text* pText_;			    //コインの数表示する用

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
	void Draw() override;

	//開放
	void Release() override {};
};

