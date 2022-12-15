#include "TitleScene.h"
#include "../../Engine/Image.h"
#include "../../Engine/Input.h"
#include "../../Engine/SceneManager.h"
#include "../../Engine/Camera.h"
#include "../../Player.h"
#include "../../Engine/Model.h"
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
	//Model::SetBrightness(hModel_, 1.0f);

	///////////////カメラ///////////////////

	Camera::SetPosition(XMFLOAT3(0, 0, 0));
	Camera::SetTarget(XMFLOAT3(0, 0, 1));

}

//更新
void TitleScene::Update()
{
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

void TitleScene::StartUpdate()
{
}
