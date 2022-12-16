#include "TitleModelPlayer.h"
#include "../Engine/Model.h"
#include "../Engine/Camera.h"
#include "../Engine/Input.h"

//コンストラクタ
TitleModelPlayer::TitleModelPlayer(GameObject* parent)
	:GameObject(parent, "TitleModelPlayer"), hModel_(-1)
{
}

//初期化
void TitleModelPlayer::Initialize()
{
	//モデルデータロード
	hModel_ = Model::Load("Star_Main_Character.fbx");
	assert(hModel_ >= ZERO);

	//アニメーション
	Model::SetAnimFlag(hModel_, true);
	Model::SetAnimFrame(hModel_, 1, 60, 1.0f);
}

//更新の前に一回呼ばれる関数
void TitleModelPlayer::StartUpdate()
{
}

//更新
void TitleModelPlayer::Update()
{
	//if (Input::IsKeyDown(DIK_4))
	//{
	//	Camera::SetCameraVibration(0.4f);
	//}

	/////////////////カメラ///////////////////

	//Camera::SetPosition(XMFLOAT3(0, 0, 5));
	//Camera::SetTarget(XMFLOAT3(0, 0, 0));
}

//描画
void TitleModelPlayer::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//解放
void TitleModelPlayer::Release()
{
}
