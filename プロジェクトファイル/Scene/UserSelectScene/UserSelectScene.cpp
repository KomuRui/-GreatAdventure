#include "UserSelectScene.h"
#include "../../Engine/Image.h"
#include "../../Engine/Input.h"
#include "../../Engine/SceneManager.h"
#include "../../Engine/Camera.h"
#include "../../Engine/Model.h"
#include "../../Engine/ImGuiSet.h"
#include "../../Engine/CreateStage.h"
#include "../../OtherObject/SelectPlanetController.h"

//コンストラクタ
UserSelectScene::UserSelectScene(GameObject* parent)
	: GameObject(parent, "UserSelectScene"), hModel_(-1)
{
}

//初期化
void UserSelectScene::Initialize()
{
	///////////////画像データのロード///////////////////

	hModel_ = Model::Load("Stage/UserSelect/Model/BackGroundModel.fbx");
	assert(hModel_ >= ZERO);

	//背景のモデルを少し光らせる
	Model::SetBrightness(hModel_, BRIGHTNESS);

	/////////////////ファイル読み込んでステージの各オブジェクト設置///////////////////

	CreateStage* pCreateStage = new CreateStage;
	pCreateStage->LoadFileCreateStage(GetParent(), "Stage/UserSelect/StageInformation/UserSelectScene1.txt");

	/////////////////ステージ設置するために必要なGUI///////////////////

	Instantiate<ImGuiSet>(GetParent());

	///////////////カメラ///////////////////

	Camera::SetPosition(CAM_POS);
	Camera::SetTarget(CAM_TAR);
	Camera::SetFieldAngle(45);
}

//更新の前に一度だけ呼ばれる更新
void UserSelectScene::StartUpdate()
{
}

//更新
void UserSelectScene::Update()
{
	//背景回転
	transform_.rotate_.y += RATATION_SPEED;

	SelectPlanetController::Update();
}

//描画
void UserSelectScene::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void UserSelectScene::Release()
{
}

