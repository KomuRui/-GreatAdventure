#pragma once
#include "StageModelBase.h"

/// <summary>
/// �X�e�[�W��I�����鎞��4�Ԗڂ̃X�e�[�W
/// </summary>
class FourthStageModel : public StageModelBase
{

public:

	//�R���X�g���N�^
	FourthStageModel(GameObject* parent, std::string ModelPath, std::string name);

	//������
	void ChildInitialize()override;

	//�X�V
	void ChildUpdate()override;
};

