#include "TitleModelPrincess.h"
#include "../Engine/Model.h"

//定数
namespace
{
	static const int START_FRAME = 1;	  //開始フレーム
	static const int END_FRAME = 60;      //終了フレーム
	static const float ANIM_SPEED = 1.0f; //アニメーションの再生速度
}

//コンストラクタ
TitleModelPrincess::TitleModelPrincess(GameObject* parent)
	:GameObject(parent, "TitleModelPrincess"), hModel_(-1)
{
}

//初期化
void TitleModelPrincess::Initialize()
{
	//モデルデータロード
	hModel_ = Model::Load("Star_Main_Character2.fbx");
	assert(hModel_ >= ZERO);

	//アニメーション
	Model::SetAnimFlag(hModel_, true);
	Model::SetAnimFrame(hModel_, START_FRAME, END_FRAME, ANIM_SPEED);
}

//更新の前に一回呼ばれる関数
void TitleModelPrincess::StartUpdate()
{
}

//更新
void TitleModelPrincess::Update()
{
}

//描画
void TitleModelPrincess::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//解放
void TitleModelPrincess::Release()
{
}
