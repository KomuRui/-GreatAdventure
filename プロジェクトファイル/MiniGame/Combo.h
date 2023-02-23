#pragma once
#include "../Engine/ResourceManager/Text.h"

/// <summary>
/// ミニゲームに登場するコンボ
/// </summary>
class Combo
{
	Text* pComboText_;           //コンボの文字表示するテキスト
	Text* pComboNumText_;        //コンボ数表示するテキスト
	XMFLOAT2 comboPositiom_;     //テキストのポジション
	XMFLOAT2 numberPositiom_;    //数字のポジション
	int ComboTotalCount_;        //どのくらいコンボしているか
	float scale_;                //拡大率

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Combo();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	///////////////////////////////Combo関数////////////////////////////////////

	/// <summary>
	/// コンボ加算
	/// </summary>
	void AddCombo();

	/// <summary>
	/// 文字の拡大率をセット
	/// </summary>
	void SetTextScale(const float& scale);

	/// <summary>
	/// コンボの数リセット
	/// </summary>
	void ComboReset();

};

