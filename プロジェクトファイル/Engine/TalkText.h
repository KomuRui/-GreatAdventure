#pragma once
#include "Text.h"

/// <summary>
/// モブが話すときに使うクラス
/// </summary>
class TalkText
{
	//表示する文字
	std::string text_;

public:

	//コンストラクタ
	TalkText() {};

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="text">表示したい文字列</param>
	void Initialize(std::string text);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
};

