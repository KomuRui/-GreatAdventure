#include "ThirdStageModel.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/CreateStage.h"

//定数
namespace
{
	static const XMFLOAT4 INITIALIZE_AMBIENT = { -0.7, -0.7, -0.7, ZERO }; //初期アンビエント値
	static const float ROTATION_ADD_VALUE = 0.25f;	//回転する時の加算する値
}

//コンストラクタ
ThirdStageModel::ThirdStageModel(GameObject* parent, std::string ModelPath, std::string name)
	:StageModelBase(parent,ModelPath,name)
{
}

//初期化
void ThirdStageModel::ChildInitialize()
{
	//アンビエント設定
	Model::SetAmbient(hModel_, INITIALIZE_AMBIENT);
}

//更新
void ThirdStageModel::ChildUpdate()
{
	transform_.rotate_.y += ROTATION_ADD_VALUE;
}
