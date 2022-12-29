#pragma once
#include "../Mob.h"

//コインの型(別のクラスでも設定したいので外に出す)
enum CoinType
{
	RotationType = 0, //回転状態
	BlockCoinType,    //ブロックから出現したコイン
};

/// <summary>
/// コインクラス
/// </summary>
class Coin : public Mob
{
	//型
	int type_;

	//符号
	int sign_;

	//タイムメソッドの種類
	enum  TimeMethodType
	{
		SignChange = 0, //符号チェンジ
		Kill            //自身削除
	};

	//どのタイムメソッドを呼ぶか
	int timeMethodStatus_;

public:

	//コンストラクタ
	Coin(GameObject* parent, std::string modelPath, std::string name);

	//更新の前に一度だけ呼ばれる関数
	void ChildStartUpdate() override;

	//更新
	void ChildUpdate() override;

	//当たり判定
	void OnCollision(GameObject* pTarget) override;

	//指定した時間で呼ばれるメソッド
	void TimeMethod() override;

	/// <summary>
	/// ブロックからコイン出た時の挙動
	/// </summary>
	void BlockCoinBehavior();

	/// <summary>
	/// 回転
	/// </summary>
	void Rotation();

	/// <summary>
	/// 型をセット
	/// </summary>
	/// <param name="num">セットしたい型</param>
	void SetType(const int& num) { type_ = num; }
};
