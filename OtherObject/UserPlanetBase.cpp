#include "UserPlanetBase.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"

//コンストラクタ
UserPlanetBase::UserPlanetBase(GameObject* parent, std::string modelPath, std::string name)
	:GameObject(parent, name), hModel_(-1), ModelNamePath_(modelPath)
{
}

//初期化
void UserPlanetBase::Initialize()
{
	//モデルデータロード
	hModel_ = Model::Load(ModelNamePath_);
	assert(hModel_ >= ZERO);
}

//更新の前に一回呼ばれる関数
void UserPlanetBase::StartUpdate()
{
}

//更新
void UserPlanetBase::Update()
{
	//少し回転させる
	transform_.rotate_.y += RATATION_SPEED;
}

//描画
void UserPlanetBase::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//解放
void UserPlanetBase::Release()
{
}
