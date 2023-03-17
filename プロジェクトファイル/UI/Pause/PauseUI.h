#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/ResourceManager/CreateStage.h"

/// <summary>
/// ポーズUI
/// </summary>
class PauseUI
{
	//各UI作成用
	CreateStage* pCreateUI_;

	//UIを描画しているか
	bool isDrawUI_;

public:

	//コンストラクタ
	PauseUI();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// UI作成
	/// </summary>
	void CreateUI();

	/// <summary>
	/// すべて削除
	/// </summary>
	void AllRelease();

	/// <summary>
	/// UIを描画しているかどうか
	/// </summary>
	/// <returns>trueなら描画している</returns>
	bool isDrawUI() { return isDrawUI_; }
};

