#pragma once
#include <string>

//フェードの状態の列挙型
enum FadeStatus
{
	NOOP,			 //何もしない
	DRAW,			 //画像だけ表示
	FADE_CIRCLE_IN,  //円のフェードイン
	FADE_CIRCLE_OUT, //円のフェードアウト
	FADE_NORMAL_IN,  //通常のフェードイン
	FADE_NORMAL_OUT, //通常のフェードアウト
	FADE_GAME_OVER	 //ゲームオーバー 
};

/// <summary>
/// フェードを行うときに使う(大体１度に１回しか使われないのでnamespace)
/// </summary>
namespace Fade
{
	///////////////////////////////関数//////////////////////////////////

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// シーン遷移の時の初期化
	/// </summary>
	void SceneTransitionInitialize();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	///////////////////////////////フェード用関数////////////////////////////////////

	/// <summary>
	/// 普通の画像を表示
	/// </summary>
	void NormalDraw();

	/// <summary>
	/// 状態によって呼ぶ関数分ける
	/// </summary>
	void FadeDraw();

	/// <summary>
	/// フェードイン描画
	/// </summary>
	void FadeInCircleDraw();

	/// <summary>
	/// フェードアウト描画
	/// </summary>
	void FadeOutCircleDraw();

	/// <summary>
	/// フェードイン描画
	/// </summary>
	void FadeInNormalDraw();

	/// <summary>
	/// フェードアウト描画
	/// </summary>
	void FadeOutNormalDraw();

	/// <summary>
	/// ゲームオーバー描画
	/// </summary>
	void GameOverDraw();

	/// <summary>
	/// 状態をセット
	/// </summary>
	/// <param name="status">セットしたい状態</param>
	/// <param name="filename"></param>
	void SetFadeStatus(int status, std::string filename = "");

	/// <summary>
	/// 現在の状態を取得
	/// </summary>
	/// <returns>現在の状態</returns>
	int GetFadeStatus();

	/// <summary>
	/// 通常のフェードが透明じゃないかどうか
	/// </summary>
	/// <returns>透明じゃないならtrue</returns>
	bool isNormalFadeNotTransparency();
}

