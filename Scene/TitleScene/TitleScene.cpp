#include "TitleScene.h"
#include "../../Engine/Image.h"
#include "../../Engine/Input.h"
#include "../../Engine/SceneManager.h"
#include "../../Engine/Camera.h"
#include "../../Player.h"
#include "../../Engine/Model.h"
#include "../../Engine/ImGuiSet.h"
#include "../../Engine/Light.h"
#include "../../Engine/CreateStage.h"

//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hModel_(-1)
{
}

//初期化
void TitleScene::Initialize()
{
	///////////////画像データのロード///////////////////

	hModel_ = Model::Load("TitleScene/Model/BackGroundModel.fbx");
	assert(hModel_ >= ZERO);

	//背景のモデルを少し光らせる
	Model::SetBrightness(hModel_, 1.5f);

	/////////////////ステージ設置するために必要なGUI///////////////////

	Instantiate<ImGuiSet>(GetParent());

	/////////////////ファイル読み込んでステージの各オブジェクト設置///////////////////

	CreateStage* pCreateStage = new CreateStage;
	pCreateStage->LoadFile(GetParent(), "TitleScene/StageInformation/TitleScene1.txt");

	///////////////カメラ///////////////////

	Camera::SetPosition(XMFLOAT3(0, 0, 5));
	Camera::SetTarget(XMFLOAT3(0, 0, 0));

}

//更新の前に一度だけ呼ばれる更新
void TitleScene::StartUpdate()
{
}

//更新
void TitleScene::Update()
{
	transform_.rotate_.y += 0.5;
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

