#pragma once
#include "ButtonBase.h"

/// <summary>
/// 新しいファイル作るときのキャンセルボタン
/// </summary>
class NewFileCancelButton : public ButtonBase
{

	//選択されていないときの画像番号
	int hNotSelectPict_;

public:

	//コンストラクタ
	NewFileCancelButton(GameObject* parent, std::string modelPath, std::string name);

	/// <summary>
	/// 選択画像を設定
	/// </summary>
	void SetSelectImage();

	/// <summary>
	/// 選択されていないときの画像を設定
	/// </summary>
	void SetNotSelectImage();

	/// <summary>
	/// 戻る
	/// </summary>
	void Back();

	/// <summary>
	/// アイコン選択へ
	/// </summary>
	void GoIconSelect();
};

