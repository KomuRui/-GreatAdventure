#include "Mob.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

//コンストラクタ
Mob::Mob(GameObject* parent, std::string modelPath)
	: GameObject(parent, "Mob"), hModel_(-1), ModelNamePath_(modelPath)
{

}

//初期化
void Mob::Initialize()
{

	///////////////モデルデータのロード///////////////////

	hModel_ = Model::Load(ModelNamePath_);
	assert(hModel_ >= 0);

	///////////////transform///////////////////

}

//更新
void Mob::Update()
{
}

//描画
void Mob::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Mob::Release()
{
}

void Mob::StartUpdate()
{
}
