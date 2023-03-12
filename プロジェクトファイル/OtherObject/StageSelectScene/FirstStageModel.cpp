#include "FirstStageModel.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/CreateStage.h"
#include "BaseSelectStage.h"

//�萔
namespace
{
	static const float ROTATION_ADD_VALUE = 0.25f;	//��]���鎞�̉��Z����l
}

//�R���X�g���N�^
FirstStageModel::FirstStageModel(GameObject* parent, std::string ModelPath, std::string name)
	:StageModelBase(parent,ModelPath, name)
{
}

//������
void FirstStageModel::ChildInitialize()
{
	//�`�F�b�N�|�C���g���f���ǉ�
	((BaseSelectStage*)GetParent())->SetCheckPointModel(static_cast<int>(CheckPoint::FIRST),this);
}

//�X�V
void FirstStageModel::ChildUpdate()
{
	transform_.rotate_.y += ROTATION_ADD_VALUE;
}