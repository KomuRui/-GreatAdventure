#pragma once
#include "../../Manager/SceneManager/SceneManager.h"

/// <summary>
/// 日本語のテキスト管理
/// </summary>
namespace TextManager
{
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 文字の対応する番号を取得
	/// </summary>
	/// <param name="text">使いたい文字</param>
	/// <returns>対応する番号</returns>
	int GetNumber(wchar_t t);

	/// <summary>
	/// シーンIDをゲット
	/// </summary>
	/// <param name="id">現在のシーンのID</param>
	/// <returns>現在のシーンのIDで使う文字を取得</returns>
	std::string GetText(SCENE_ID nowId);
}
