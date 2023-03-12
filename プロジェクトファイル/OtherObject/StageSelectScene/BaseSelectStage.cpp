#include "BaseSelectStage.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/CreateStage.h"

//定数
namespace
{
	static const int ROTATION_ANGLE_VALUE = 45; //回転角度
}

//コンストラクタ
BaseSelectStage::BaseSelectStage(GameObject* parent)
	:GameObject(parent, "BaseSelectStage"), hModel_(-1)
{
}

//初期化
void BaseSelectStage::Initialize()
{
	///////////////////各ステージ作成////////////////////////
	
	CreateStage* pCreateStage_ = new CreateStage;
	//pCreateStage_->LoadFileCreateStage(this, "Stage/StageSelect/StageInformation/StageSelectStage.txt");

	///////////////モデルデータのロード///////////////////

	hModel_ = Model::Load("Stage/StageSelect/Base.fbx");
	assert(hModel_ >= ZERO);

	/////////////////明るさ設定/////////////////

	Model::SetBrightness(hModel_, 1.0f);

	///////////////カメラの設定///////////////////

	Camera::SetPosition(XMFLOAT3(0,50,80));
	//Camera::SetTarget(XMFLOAT3(0,0,0));

	transform_.scale_ = { 1,1,1 };
}

//更新
void BaseSelectStage::Update()
{
	if (Input::IsPadStickRightL()) transform_.rotate_.y += ROTATION_ANGLE_VALUE;
	if (Input::IsPadStickLeftL()) transform_.rotate_.y -= ROTATION_ANGLE_VALUE;
}

//描画
void BaseSelectStage::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

