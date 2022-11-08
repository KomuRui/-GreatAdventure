#include "Mob.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

//コンストラクタ
Mob::Mob(GameObject* parent, std::string modelPath,std::string name)
	: GameObject(parent, name), hModel_(-1), ModelNamePath_(modelPath)
{
}

//初期化
void Mob::Initialize()
{
	///////////////モデルデータのロード///////////////////

	hModel_ = Model::Load(ModelNamePath_);
	assert(hModel_ >= 0);

	SetEmission();

	///////////////元々あるTransform.Rotateを使わないためFlagをTrueにする///////////////////

	transform_.mFlag_ = true;

	////////////////////継承先で新たに初期化の内容追加する用///////////////////////

	ChildInitialize();
}

//更新の前に一回だけ呼ばれる関数
void Mob::StartUpdate()
{
	ChildStartUpdate();
}

//更新
void Mob::Update()
{
	//継承先ごとに動きを変えれる
	UpdateMove();
}

//描画
void Mob::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	ChildDraw();
}

//開放
void Mob::Release()
{
}




