#include "ThirdStageModel.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/CreateStage.h"

//�R���X�g���N�^
ThirdStageModel::ThirdStageModel(GameObject* parent, std::string ModelPath, std::string name)
	:StageModelBase(parent,ModelPath,name)
{
}

//������
void ThirdStageModel::ChildInitialize()
{
	Model::SetAmbient(hModel_,XMFLOAT4(-0.7, -0.7, -0.7, 0));
}
