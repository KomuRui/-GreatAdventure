#include "BaseSelectStage.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/CreateStage.h"
#include "../../Engine/ResourceManager/Easing.h"
#include "../../UI/StageSelectScene/StageSelectTextUI.h"

//定数
namespace
{
	static const XMFLOAT3 CAM_POS = { 0,20,70 }; //カメラのポジション
	static const XMFLOAT3 CAM_TAR = { 0,-10,0 }; //カメラのターゲット
	static const int ROTATION_ANGLE_VALUE = 45;  //回転角度
	static const float EASING_TIME = 1.0f;       //イージングにかかる時間
}

//コンストラクタ
BaseSelectStage::BaseSelectStage(GameObject* parent)
	:GameObject(parent, "BaseSelectStage"), hModel_(-1), lookCheckPoint_(static_cast<int>(CheckPoint::FIRST))
{
}

//初期化
void BaseSelectStage::Initialize()
{
	///////////////////各ステージ作成////////////////////////
	
	CreateStage* pCreateStage_ = new CreateStage;
	pCreateStage_->LoadFileCreateStage(this, "Stage/StageSelect/StageInformation/StageSelectStage.txt");
	pCreateStage_->LoadFileCreateStage(GetParent(), "Stage/StageSelect/StageInformation/StageSelectUI.txt");
	Instantiate<StageSelectTextUI>(GetParent());

	///////////////モデルデータのロード///////////////////

	hModel_ = Model::Load("Stage/StageSelect/Base.fbx");
	assert(hModel_ >= ZERO);

	/////////////////イージング初期化/////////////////

	ARGUMENT_INITIALIZE(pEasing_, new EasingMove(&transform_.rotate_, transform_.rotate_, transform_.rotate_,0.0f,Easing::InQuint));

	/////////////////明るさ設定/////////////////

	Model::SetBrightness(hModel_, 1.0f);

	///////////////カメラの設定///////////////////

	Camera::SetPosition(CAM_POS);
	Camera::SetTarget(CAM_TAR);
}

//更新
void BaseSelectStage::Update()
{
	//動きが終わっているかどうか
	bool isFinish = pEasing_->Move();

	//動きが終わっているかつスティックを傾けたのなら回転させる
	if (Input::IsPadStickRightL() && isFinish)
	{
		//回転
		XMFLOAT3 afterRotate = transform_.rotate_;
		afterRotate.y += ROTATION_ANGLE_VALUE;
		pEasing_->Reset(&transform_.rotate_,transform_.rotate_, afterRotate, EASING_TIME, Easing::OutCubic);

		//チェックポイント計算
		CheckPointCalc(1);
	}
	else if (Input::IsPadStickLeftL() && isFinish)
	{
		//回転
		XMFLOAT3 afterRotate = transform_.rotate_;
		afterRotate.y -= ROTATION_ANGLE_VALUE;
		pEasing_->Reset(&transform_.rotate_, transform_.rotate_, afterRotate, EASING_TIME,Easing::OutCubic);

		//チェックポイント計算
		CheckPointCalc(-1);
	}
}

//描画
void BaseSelectStage::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//チェックポイント計算
void BaseSelectStage::CheckPointCalc(int sige)
{
	//見ていたチェックポイントがnullptrじゃなければ選択状態削除
	if (table_[lookCheckPoint_] != nullptr)
		table_[lookCheckPoint_]->SetSelect(false);

	//マイナス方向
	if (sige < ZERO)
	{
		//もし最初のチェックポイントなら
		if (lookCheckPoint_ == static_cast<int>(CheckPoint::FIRST))
		{
			ARGUMENT_INITIALIZE(lookCheckPoint_, static_cast<int>(CheckPoint::NONE4));
		}
		else
			lookCheckPoint_--;
	}
	//プラス方向
	else
	{
		//もし最後のチェックポイントなら
		if (lookCheckPoint_ == static_cast<int>(CheckPoint::NONE4))
		{
			ARGUMENT_INITIALIZE(lookCheckPoint_, static_cast<int>(CheckPoint::FIRST));
		}
		else
			lookCheckPoint_++;
	}


	//新たに見たチェックポイントがnullptrじゃなければ選択状態に
	if (table_[lookCheckPoint_] != nullptr)
		table_[lookCheckPoint_]->SetSelect(true);
}
