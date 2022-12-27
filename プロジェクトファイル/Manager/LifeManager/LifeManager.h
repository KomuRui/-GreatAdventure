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
	/// ダメージ食らった時に呼ぶメソッド
	/// </summary>
	/// <param name="damage">ダメージの強さ</param>
	void Damage(int damage);

	/// <summary>
	/// 死んだどうか
	/// </summary>
	/// <returns>trueなら死んだ,falseならまだ生きてる</returns>
	bool IsDie();
}