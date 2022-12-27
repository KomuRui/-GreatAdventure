#pragma once
#include "Block.h"

//�A�C�e���u���b�N�̌^(�Ⴄ�ꏊ�ł��g�������̂ŊO�ɏo��)
enum ItemBlockType
{
	ItemBlockNormal,  //����
	ItemBlockRotation //��]
};

/// <summary>
/// �A�C�e���u���b�N�N���X
/// </summary>
class ItemBlock : public Block
{
	//�^
	int type_;

public:

	//�R���X�g���N�^
	ItemBlock(GameObject* parent, std::string modelPath, std::string name);

	//�X�V
	void BlockChildUpdate() override;

	/// <summary>
	/// �u���b�N�̓���
	/// </summary>
	void Move();

	/// <summary>
	/// �^�Z�b�g
	/// </summary>
	/// <param name="num">�Z�b�g�������^</param>
	void SetStatus(const int& num){ type_ = num;}
};
