#pragma once

/// <summary>
/// Playerのライフ管理
/// </summary>
namespace LifeManager
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
	/// ダメージ食らった時に呼ぶメソッド
	/// </summary>
	void Damage();

	/// <summary>
	/// HPUI描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 画像の拡大縮小
	/// </summary>
	void ImageScaling();

	/// <summary>
	/// 死んだどうか
	/// </summary>
	/// <returns>trueなら死んだ,falseならまだ生きてる</returns>
	bool IsDie();
}