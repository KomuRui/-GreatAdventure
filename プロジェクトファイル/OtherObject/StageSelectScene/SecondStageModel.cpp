#include "SecondStageModel.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/CreateStage.h"

//定数
namespace
{
	static const XMFLOAT3 ROTATION_MODEL_POSITION = { -39.5f, ZERO, 1.2f }; //回転モデルのポジション
	static const float ROTATION_ADD_VALUE = 0.30f;	//回転する時の加算する値
}

//コンストラクタ
SecondStageModel::SecondStageModel(GameObject* parent, std::string ModelPath, std::string name)
	:StageModelBase(parent,ModelPath,name), hRotationModel_(-1)
{
}

//初期化
void SecondStageModel::ChildInitialize()
{
	///////////////モデルデータのロード///////////////////

	hRotationModel_ = Model::Load("Stage/StageSelect/second/secondStageModel2.fbx");
	assert(hRotationModel_ >= ZERO);

	/////////////////明るさ設定/////////////////

	Model::SetBrightness(hRotationModel_, 1.0f);

	//////////////////トランスフォーム初期化/////////////////////

	ARGUMENT_INITIALIZE(tRotation_.position_, ROTATION_MODEL_POSITION);
	ARGUMENT_INITIALIZE(tRotation_.pParent_, transform_.pParent_);
}

//更新
void SecondStageModel::ChildUpdate()
{
	//回転
	tRotation_.rotate_.y += ROTATION_ADD_VALUE;
}

//描画
void SecondStageModel::ChildDraw()
{
	Model::SetTransform(hRotationModel_, tRotation_);
	Model::Draw(hRotationModel_);
}