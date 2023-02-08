#pragma once
#include "../../Button/ButtonBase.h"

//前定義
class EasingMove;

/// <summary>
/// ユーザ選んでゲームスタートするときのキャンセルボタン
/// </summary>
class UserGameCancelButton : public ButtonBase
{

	int hSelectPict_;    //選択されているときの画像番号
	int hNotSelectPict_; //選択されていないときの画像番号

	XMFLOAT3 easingBeforePos_; //イージングの移動前ポジション
	XMFLOAT3 easingAfterPos_;  //イージングの移動後ポジション

	EasingMove* pEasingMove_;  //UIをイージングで移動させる用

public:

	//コンストラクタ
	UserGameCancelButton(GameObject* parent, std::string modelPath, std::string name);

	////////////////////オーバーライドする関数/////////////////////////

	/// <summary>
	/// 初期化
	/// </summary>
	void ChildInitialize() override;

	/// <summary>
	/// 更新
	/// </summary>
	void ChildButtonUpdate() override;

	/// <summary>
	/// ボタンが押されたら何するか
	/// </summary>
	/// <param name="p">実行したい関数ポインタ</param>
	void IsButtonPush() override;

	/// <summary>
	/// ボタンが選択された瞬間に何をするか
	/// </summary>
	/// <param name="p">実行したい関数ポインタ</param>
	void IsButtonSelect() override;

	/// <summary>
	/// ボタンが選択解除された瞬間に何をするか
	/// </summary>
	/// <param name="p">実行したい関数ポインタ</param>
	void IsButtonSelectRelease() override;
};

