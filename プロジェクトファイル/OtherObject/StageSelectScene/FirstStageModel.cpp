#include "FirstStageModel.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/CreateStage.h"
#include "BaseSelectStage.h"

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

//初期化
void FirstStageModel::ChildInitialize()
{
	//チェックポイントモデル追加
	((BaseSelectStage*)GetParent())->SetCheckPointModel(static_cast<int>(CheckPoint::FIRST),this);
}

//更新
void FirstStageModel::ChildUpdate()
{
	transform_.rotate_.y += ROTATION_ADD_VALUE;
}