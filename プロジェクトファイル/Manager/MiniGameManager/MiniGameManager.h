#pragma once

//ミニゲームの状態
enum class MiniGameStatus
{
	NOT_START = 0, //まだ開始していない
	PLAY,          //プレイ中
	END            //ミニゲーム終了
};

/// <summary>
/// ミニゲームの管理をする
/// </summary>
namespace MiniGameManager
{
	///////////////////////////////関数//////////////////////////////////

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 描画(コインの取得数やコンボ数,タイムの表示)
	/// </summary>
	void Draw();

	/// <summary>
	/// 結果表示
	/// </summary>
	void ResultDraw();

	/// <summary>
	/// 開始しているか
	/// </summary>
	/// <returns>trueなら開始している</returns>
	bool IsPlay();

	/// <summary>
	/// 開始しているかをセット
	/// </summary>
	void ChangeMiniGameStatus(MiniGameStatus status);

	/// <summary>
	/// ミニゲームの状態をゲット
	/// </summary>
	/// <returns>ミニゲームの状態</returns>
	MiniGameStatus GetMiniGameStatus();

	/// <summary>
	/// 距離を設定
	/// </summary>
	/// <param name="dis">設定したい距離</param>
	void SetResultDis(const int& dis);
};

