#include "UserSelectStage.h"
#include "../../Engine/Model.h"
#include "../../Engine/Light.h"
#include "../../Engine/Camera.h"
#include "../../Gimmick/Warp.h"
#include "../../Engine/CreateStage.h"
#include "../../OtherObject/SelectPlanetController.h"
#include "../../UI/UserSelectScene/UserSelectSceneUI.h"

//定数
namespace
{
	static const float RATATION_SPEED = 0.1f;    //回転速度
	static const float BRIGHTNESS = 1.5f;		 //背景モデルの明るさ
	static const XMFLOAT3 CAM_POS = { 0, 0, 5 }; //カメラの位置
	static const XMFLOAT3 CAM_TAR = { 0, 0, 0 }; //カメラのターゲット
}

//コンストラクタ
UserSelectStage::UserSelectStage(GameObject* parent)
	:Stage(parent, "UserSelectStage")
{
	//画角
	ARGUMENT_INITIALIZE(fieldAngle_,45);
}

//初期化
void UserSelectStage::Initialize()
{
	/////////////////ファイル読み込んでステージの各オブジェクト設置///////////////////

	pCreateStage_ = new CreateStage;
	pCreateStage_->LoadFileCreateStage(this, "Stage/UserSelect/StageInformation/UserSelectScene1.txt");

	/////////////////////モデルデータのロード///////////////////////

	hModel_[Space] = Model::Load("Stage/UserSelect/Model/BackGroundModel.fbx");

	///////////////////////////各種設定/////////////////////////////

	//Spaceモデルの明るさ設定
	Model::SetBrightness(hModel_[Space], BRIGHTNESS);

	////////////////////UI表示//////////////////////

	Instantiate<UserSelectSceneUI>(GetParent());

	///////////////カメラ///////////////////

	Camera::SetPosition(CAM_POS);
	Camera::SetTarget(CAM_TAR);
	Camera::SetFieldAngle(fieldAngle_);
}

//更新
void UserSelectStage::Update()
{
	//背景回転させる
	tSpace_.rotate_.y += RATATION_SPEED;

	//ユーザー情報の管理している名前空間の更新を呼ぶ
	SelectPlanetController::Update();
}

//描画
void UserSelectStage::Draw()
{
	Model::SetTransform(hModel_[Space], tSpace_);
	Model::Draw(hModel_[Space]);
}

//解放
void UserSelectStage::Release()
{
}
