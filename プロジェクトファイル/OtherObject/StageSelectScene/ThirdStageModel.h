#pragma once
#include "StageModelBase.h"


/// <summary>
/// �X�e�[�W��I�����鎞��3�Ԗڂ̃X�e�[�W
/// </summary>
class ThirdStageModel : public StageModelBase
{

public:

	//�R���X�g���N�^
	ThirdStageModel(GameObject* parent, std::string ModelPath, std::string name);

	//������
    void ChildInitialize()override;

	//�X�V
	void ChildUpdate()override;
};

