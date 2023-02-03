#pragma once
#include "../../Engine/GameObject.h"
#include "../../Engine/Time.h"

//前定義
class CreateStage;
class EasingMove;

/// <summary>
/// ユーザー情報選択シーンのアイコンを選択する時のUI
/// </summary>
class IconSelectUI : public GameObject
{
	//UIとか表示する用
	CreateStage* pCreateStage_;

	//UIをイージングで移動させる用
	EasingMove* pEasingMove_;

	//イージング変更したかどうか
	bool isEasingChange_;

public:

	//コンストラクタ
	IconSelectUI(GameObject* parent);

	/////////////////////オーバーライドする関数//////////////////////

	//初期化
	void Initialize() override;

	//更新の前に一回呼ばれる関数
	void StartUpdate() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	/// <summary>
	/// イージングの動き方変更
	/// </summary>
	void ChangeEasingMove();
};

