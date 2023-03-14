#pragma once
#include "../../Stage.h"

/// <summary>
/// ユーザー情報選択シーンのステージ
/// </summary>
class UserSelectStage : public Stage
{

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	UserSelectStage(GameObject* parent);

	///////////////////オーバライドする関数///////////////////////

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

	////////////////////////関数//////////////////////////

	/// <summary>
	/// ステージUIを作成
	/// </summary>
	void CreateStageUI();
};

