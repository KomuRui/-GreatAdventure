#pragma once
#include "StageModelBase.h"

/// <summary>
/// �X�e�[�W��I�����鎞�̂P�Ԗڂ̃X�e�[�W
/// </summary>
class FirstStageModel : public StageModelBase
{

public:

	//�R���X�g���N�^
	FirstStageModel(GameObject* parent,std::string ModelPath,std::string name);

	//������
	void ChildInitialize() override {};

	//�X�V
	void ChildUpdate()override;
};

