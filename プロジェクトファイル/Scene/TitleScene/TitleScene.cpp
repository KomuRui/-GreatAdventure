#include "TitleScene.h"
#include "../../Engine/Image.h"
#include "../../Engine/Input.h"
#include "../../Engine/SceneManager.h"
#include "../../Engine/Camera.h"
#include "../../Player.h"
#include "../../Engine/Model.h"
#include "../../Engine/Light.h"
#include "../../Engine/CreateStage.h"
#include "../../OtherObject/TitleModel.h"

//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hModel_(-1)
{
}

//初期化
void TitleScene::Initialize()
{
	///////////////画像データのロード///////////////////

	hModel_ = Model::Load("Stage/Title/Model/BackGroundModel.fbx");
	assert(hModel_ >= ZERO);

	//背景のモデルを少し光らせる
	Model::SetBrightness(hModel_, BRIGHTNESS);


	/////////////////ファイル読み込んでステージの各オブジェクト設置///////////////////

	CreateStage* pCreateStage = new CreateStage;
	pCreateStage->LoadFileCreateStage(GetParent(), "Stage/Title/StageInformation/TitleScene1.txt");

	///////////////カメラ///////////////////

	Camera::SetPosition(CAM_POS);
	Camera::SetTarget(CAM_TAR);

}

//更新の前に一度だけ呼ばれる更新
void TitleScene::StartUpdate()
{
}

//更新
void TitleScene::Update()
{
	//背景回転させる
	transform_.rotate_.y += RATATION_SPEED;

	//AとRトリガー同時押しでシーン移動
	if (Input::IsPadButton(XINPUT_GAMEPAD_A) && Input::GetPadTrrigerR())
	{
		//シーン移動の際のエフェクト表示
		TitleModel* pTitleModel = (TitleModel*)FindObject("TitleModel");

		//nullptrじゃなければ
		if(pTitleModel !=nullptr)
			pTitleModel->SceneChangeEffect();

		//エフェクトが広がったときにシーン移行したいのでタイムメソッドを使って指定した時間がたったころに呼ぶ
		SetTimeMethod(0.5f);
	}
}

//描画
void TitleScene::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void TitleScene::Release()
{
}

//指定した時間で呼ばれるメソッド
void TitleScene::TimeMethod()
{
	//ロードの時の描画を設定しない
	GameManager::GetpSceneManager()->SetLoadDrawFlag(false);
	GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_USER_SELECT);
}