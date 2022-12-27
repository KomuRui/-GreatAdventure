#pragma once
#include "Block.h"

//アイテムブロックの型(違う場所でも使いたいので外に出す)
enum ItemBlockType
{
	ItemBlockNormal,  //普通
	ItemBlockRotation //回転
};

/// <summary>
/// アイテムブロッククラス
/// </summary>
class ItemBlock : public Block
{
	//型
	int type_;

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
	/// 型セット
	/// </summary>
	/// <param name="num">セットしたい型</param>
	void SetStatus(const int& num){ type_ = num;}
};
