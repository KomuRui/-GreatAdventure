#include "TitleModel.h"
#include "../Engine/Model.h"

//コンストラクタ
TitleModel::TitleModel(GameObject* parent)
	:GameObject(parent,"TitleModel"),hModel_(-1)
{
}

//初期化
void TitleModel::Initialize()
{
	//モデルデータロード
	hModel_ = Model::Load("TitleModel.fbx");
	assert(hModel_ >= 0);
}

//更新の前に一回呼ばれる関数
void TitleModel::StartUpdate()
{
}

//更新
void TitleModel::Update()
{
}

//描画
void TitleModel::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//解放
void TitleModel::Release()
{
}
