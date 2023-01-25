#pragma once

/// <summary>
/// DirectX環境に依存しないTime
/// </summary>
namespace Time
{
	//初期化(Mainで初期化)
	void Initialize(int FPS);

	//更新(Mainで呼び出し)
	void Update();

	/// <summary>
	/// タイムリセット
	/// </summary>
	void Reset();

	/// <summary>
	/// タイムを更新しないようにする
	/// </summary>
	void Lock();

	/// <summary>
	/// タイムを更新するようにする
	/// </summary>
	void UnLock();

	/// <summary>
	/// 今ロックしているかどうか
	/// </summary>
	/// <returns>trueならロックしている</returns>
	bool isLock();

	/// <summary>
	/// 呼び出し時点の時間を取得
	/// </summary>
	/// <returns>int型の時間</returns>
	int GetTimei();

	/// <summary>
	/// 呼び出し時点の時間を取得
	/// </summary>
	/// <returns>float型の時間</returns>
	float GetTimef();

	/// <summary>
	/// 呼び出し時点の時間を取得
	/// </summary>
	/// <returns>double型の時間</returns>
	double GetTime();
};

