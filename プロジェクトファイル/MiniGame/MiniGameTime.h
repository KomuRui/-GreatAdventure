#pragma once
#include "../Engine/Text.h"


/// <summary>
/// ミニゲームの時間やスタートする時のカウントを表示
/// </summary>
class MiniGameTime
{	

	Text* pTimeText_;           //時間表示するための変数
	Text* pStartCountText_;     //スタートするまでのカウントを表示するための文字表示変数

	int startCount_;            //スタートするまでのカウント
	float startCountTextScale_; //スタートカウント文字の拡大率

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	MiniGameTime();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 制限時間描画
	/// </summary>
	void LimitTimeDraw();

	/// <summary>
	/// スタートカウント描画
	/// </summary>
	void StartCountDraw();
};

