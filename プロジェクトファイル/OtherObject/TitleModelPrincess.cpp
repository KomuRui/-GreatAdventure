#include "TitleModelPrincess.h"
#include "../Engine/Model.h"

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
	Model::SetAnimFrame(hModel_, 1, 60, 1.0f);
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
