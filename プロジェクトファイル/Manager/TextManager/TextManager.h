#pragma once

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
}
