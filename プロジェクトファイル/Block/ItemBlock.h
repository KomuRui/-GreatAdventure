#pragma once
#include "Block.h"
#include "../Engine/Particle.h"

//アイテムブロックの型(違う場所でも使いたいので外に出す)
enum ItemBlockType
{
	ItemBlockNormal = 0, //普通
	ItemBlockRotation    //回転
};

//アイテムブロックがドロップするアイテムの型
enum DropItemType
{
	None = 0,    //何もなし     
	OneCoin,     //コイン1
	TenCoin      //コイン10
};

/// <summary>
/// アイテムブロッククラス
/// </summary>
class ItemBlock : public Block
{
	//エフェクト表示するのに必要な変数
	Particle* pParticle_;                   

	//型
	int type_;

	//ドロップするアイテムのタイプ
	int dropItemType_;

	//コイン何枚出したかカウントする用
	int coinCount_;

public:

	//コンストラクタ
	ItemBlock(GameObject* parent, std::string modelPath, std::string name);

	//更新
	void BlockChildUpdate() override;

	/// <summary>
	/// ブロックの動き
	/// </summary>
	void Move();

	/// <summary>
	/// 当たった時のエフェクト
	/// </summary>
	void HitEffect();

	/// <summary>
	/// 継承先用のPlayerが下から当たった時の挙動
	/// </summary>
	void BlockChildHitToLowerPlayer() override;

	/// <summary>
	/// 型セット
	/// </summary>
	/// <param name="num">セットしたい型</param>
	void SetType(const int& num){ type_ = num;}

	/// <summary>
	/// ドロップするアイテムのタイプセット
	/// </summary>
	/// <param name="num">セットしたいアイテムのタイプ</param>
	void SetDropItemType(const int& num) { dropItemType_ = num; }
};
