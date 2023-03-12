#include "FirstStageModel.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/CreateStage.h"

//定数
namespace
{
	static const float ROTATION_ADD_VALUE = 0.25f;	//回転する時の加算する値
}

//コンストラクタ
FirstStageModel::FirstStageModel(GameObject* parent, std::string ModelPath, std::string name)
	:StageModelBase(parent,ModelPath, name)
{
}

//更新
void FirstStageModel::ChildUpdate()
{
	transform_.rotate_.y += ROTATION_ADD_VALUE;
}