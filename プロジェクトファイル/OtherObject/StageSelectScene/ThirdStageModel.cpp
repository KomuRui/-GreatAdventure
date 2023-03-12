#include "ThirdStageModel.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/CreateStage.h"

//�萔
namespace
{
	static const XMFLOAT4 INITIALIZE_AMBIENT = { -0.7, -0.7, -0.7, ZERO }; //�����A���r�G���g�l
	static const float ROTATION_ADD_VALUE = 0.25f;	//��]���鎞�̉��Z����l
}

//�R���X�g���N�^
ThirdStageModel::ThirdStageModel(GameObject* parent, std::string ModelPath, std::string name)
	:StageModelBase(parent,ModelPath,name)
{
}

//������
void ThirdStageModel::ChildInitialize()
{
	//�A���r�G���g�ݒ�
	Model::SetAmbient(hModel_, INITIALIZE_AMBIENT);
}

//�X�V
void ThirdStageModel::ChildUpdate()
{
	transform_.rotate_.y += ROTATION_ADD_VALUE;
}
