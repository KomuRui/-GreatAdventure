#pragma once

class ButtonBase;

/// <summary>
/// 画面に表示されているボタンを管理する
/// </summary>
namespace ButtonManager
{
	
	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 入力
	/// </summary>
	void Input(ButtonBase* button);

	/// <summary>
	/// ボタンを追加
	/// </summary>
	void AddButton(ButtonBase* button);

	/// <summary>
	/// リセットする
	/// </summary>
	void Reset();
};

