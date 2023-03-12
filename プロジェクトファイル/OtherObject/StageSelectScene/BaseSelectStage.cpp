#include "BaseSelectStage.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/CreateStage.h"
#include "../../Engine/ResourceManager/Easing.h"

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
	pCreateStage_->LoadFileCreateStage(this, "Stage/StageSelect/StageInformation/StageSelectStage.txt");
	pCreateStage_->LoadFileCreateStage(GetParent(), "Stage/StageSelect/StageInformation/StageSelectUI.txt");

	///////////////モデルデータのロード///////////////////

	hModel_ = Model::Load("Stage/StageSelect/Base.fbx");
	assert(hModel_ >= ZERO);

	/////////////////イージング初期化/////////////////

	ARGUMENT_INITIALIZE(pEasing_, new EasingMove(&transform_.rotate_, transform_.rotate_, transform_.rotate_,0.0f,Easing::InQuint));

	/////////////////明るさ設定/////////////////

	Model::SetBrightness(hModel_, 1.0f);

	///////////////カメラの設定///////////////////

	Camera::SetPosition(XMFLOAT3(0,20,70));
	Camera::SetTarget(XMFLOAT3(0,-10,0));
}

//更新
void BaseSelectStage::Update()
{
	//動きが終わっているかどうか
	bool isFinish = pEasing_->Move();

	//動きが終わっているかつスティックを傾けたのなら回転させる
	if (Input::IsPadStickRightL() && isFinish)
	{
		XMFLOAT3 afterRotate = transform_.rotate_;
		afterRotate.y += ROTATION_ANGLE_VALUE;
		pEasing_->Reset(&transform_.rotate_,transform_.rotate_, afterRotate,1.0f, Easing::OutCubic);
	}
	else if (Input::IsPadStickLeftL() && isFinish)
	{
		XMFLOAT3 afterRotate = transform_.rotate_;
		afterRotate.y -= ROTATION_ANGLE_VALUE;
		pEasing_->Reset(&transform_.rotate_, transform_.rotate_, afterRotate, 1.0f, Easing::OutCubic);
	}
}

//描画
void BaseSelectStage::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

