#pragma once

/// <summary>
/// Playerの持ってるコイン管理
/// </summary>
namespace CoinManager
{
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// シーン遷移の時の初期化
	/// </summary>
	void SceneTransitionInitialize();

	/// <summary>
	/// コイン何枚持っているか描画
	/// </summary>
	void Draw();

	/// <summary>
	/// コインの追加
	/// </summary>
	/// <param name="num">追加したいコインの数</param>
	void AddCoin(int num);

	/// <summary>
	/// コインの減少
	/// </summary>
	/// <param name="num">減少させたいコインの数</param>
	void DecrementCoin(int num);

	/// <summary>
	/// コインの数取得
	/// </summary>
	/// <returns>コインの数</returns>
	int GetCoinNum();

	/// <summary>
	/// コインの数をセット
	/// </summary>
	/// <param name="num">セットしたいコインの数</param>
	void SetCoinNum(int num);
}

