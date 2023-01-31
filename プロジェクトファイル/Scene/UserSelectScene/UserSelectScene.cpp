#include "UserSelectScene.h"
#include "../../Engine/Image.h"
#include "../../Engine/Input.h"
#include "../../Engine/SceneManager.h"
#include "../../Engine/Camera.h"
#include "../../Engine/Model.h"
#include "../../Engine/CreateStage.h"
#include "../../OtherObject/SelectPlanetController.h"
#include "../../OtherObject/UserSelectSceneUI.h"
#include "../../Manager/GameManager/GameManager.h"

//定数
namespace
{
	static const float RATATION_SPEED = 0.1f;    //回転速度
	static const float BRIGHTNESS = 1.5f;		 //背景モデルの明るさ
	static const XMFLOAT3 CAM_POS = { 0, 0, 5 }; //カメラの位置
	static const XMFLOAT3 CAM_TAR = { 0, 0, 0 }; //カメラのターゲット
}


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

	////////////////////UI表示//////////////////////

	Instantiate<UserSelectSceneUI>(GetParent());

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

	//ユーザー情報の管理している名前空間の更新を呼ぶ
	SelectPlanetController::Update();

	//Aボタンを押したなら
	if (Input::IsPadButton(XINPUT_GAMEPAD_A))
	{
		GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_TUTORIAL1);
	}
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

