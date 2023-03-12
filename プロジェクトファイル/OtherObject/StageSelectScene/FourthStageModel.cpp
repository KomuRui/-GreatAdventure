#include "FourthStageModel.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/CreateStage.h"

//コンストラクタ
FourthStageModel::FourthStageModel(GameObject* parent, std::string ModelPath, std::string name)
	:StageModelBase(parent, ModelPath,name)
{
}

//初期化
void FourthStageModel::ChildInitialize()
{
	Model::SetAmbient(hModel_, XMFLOAT4(-0.6, -0.6, -0.6, 0));
}
