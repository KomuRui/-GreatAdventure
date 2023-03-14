#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/ResourceManager/Time.h"

//前定義
class CreateStage;
class EasingMove;

/// <summary>
/// ユーザー情報選択シーンの新しいファイルを作成する時のUI
/// </summary>
class NewFileUI : public GameObject
{
	//UIとか表示する用
	CreateStage* pCreateStage_;

	//UIをイージングで移動させる用
	EasingMove* pEasingMove_;

	//イージング変更してアイコンにいくか
	bool isEasingChangeIcon_;

	//イージング変更して元に戻る
	bool isEasingChangeReturn_;

	//ボタン押すのを許可するか
	bool isButtonPushOk_;

public:

	//コンストラクタ
	NewFileUI(GameObject* parent);

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
	/// イージングの動き方変更してアイコンのUIへ
	/// </summary>
	void ChangeEasingMoveIcon();

	/// <summary>
	/// イージングの動き方変更して元にモデル
	/// </summary>
	void ChangeEasingMoveReturn();

	/// <summary>
	/// ボタン押すのを許可するか取得
	/// </summary>
	/// <returns>trueなら許可</returns>
	bool IsButtonPushOk() { return isButtonPushOk_; }
};

