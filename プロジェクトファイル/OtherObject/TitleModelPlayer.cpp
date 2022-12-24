#include "TitleModelPlayer.h"
#include "../Engine/Model.h"
#include "../Engine/Camera.h"
#include "../Engine/Input.h"

//定数
namespace
{
	static const int START_FRAME = 1;	  //開始フレーム
	static const int END_FRAME = 60;      //終了フレーム
	static const float ANIM_SPEED = 1.0f; //アニメーションの再生速度
}

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
	Model::SetAnimFrame(hModel_, START_FRAME, END_FRAME, ANIM_SPEED);
}

//更新の前に一回呼ばれる関数
void TitleModelPlayer::StartUpdate()
{
}

//更新
void TitleModelPlayer::Update()
{
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
