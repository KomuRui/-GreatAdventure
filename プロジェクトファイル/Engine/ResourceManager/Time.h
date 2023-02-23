#pragma once

/// <summary>
/// DirectX環境に依存しないTime
/// </summary>
namespace Time
{
	/// <summary>
	/// 初期化(Mainで初期化)
	/// </summary>
	/// <param name="FPS">FPS</param>
	void Initialize(int FPS);

	/// <summary>
	/// タイマー追加
	/// </summary>
	/// <returns>タイマー番号(タイマー使うときに使う)</returns>
	int Add();

	/// <summary>
	/// 更新(Mainで呼び出し)
	/// </summary>
	void Update();

	/// <summary>
	/// 解放
	/// </summary>
	void AllRelease();

	/// <summary>
	/// タイムリセット
	/// </summary>
	/// <param name="handle">リセットしたいタイマーの番号</param>
	void Reset(int handle);

	/// <summary>
	/// タイムを更新しないように
	/// </summary>
	/// <param name="handle">リセットしたいタイマーの番号</param>
	void Lock(int handle);

	/// <summary>
	/// タイムを更新するように
	/// </summary>
	/// <param name="handle">リセットしたいタイマーの番号</param>
	void UnLock(int handle);

	/// <summary>
	/// 今ロックしているかどうか
	/// </summary>
	/// <param name="handle">リセットしたいタイマーの番号</param>
	/// <returns>trueならロックしている</returns>
	bool isLock(int handle);

	/// <summary>
	/// 呼び出し時点の時間を取得
	/// </summary>
	/// <param name="handle">リセットしたいタイマーの番号</param>
	/// <returns>int型の時間</returns>
	int GetTimei(int handle);

	/// <summary>
	/// 呼び出し時点の時間を取得
	/// </summary>
	/// <param name="handle">リセットしたいタイマーの番号</param>
	/// <returns>float型の時間</returns>
	float GetTimef(int handle);

	/// <summary>
	/// 呼び出し時点の時間を取得
	/// </summary>
	/// <param name="handle">リセットしたいタイマーの番号</param>
	/// <returns>double型の時間</returns>
	double GetTime(int handle);
};

