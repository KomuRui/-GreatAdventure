#include "StageModelBase.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/CreateStage.h"


//コンストラクタ
StageModelBase::StageModelBase(GameObject* parent, std::string ModelPath, std::string name)
	:GameObject(parent, name), hModel_(-1),modelPathName_(ModelPath), isSelect_(false)
{
}

//初期化
void StageModelBase::Initialize()
{

	///////////////モデルデータのロード///////////////////

	hModel_ = Model::Load(modelPathName_);
	assert(hModel_ >= ZERO);

	/////////////////明るさ設定/////////////////

	Model::SetBrightness(hModel_, 1.0f);



	//継承先用
	ChildInitialize();
}

//更新の前に一度だけ呼ばれる関数
void StageModelBase::StartUpdate()
{
	//継承先用
	ChildStartUpdate();
}

//更新
void StageModelBase::Update()
{
	//継承先用
	ChildUpdate();
}

//描画
void StageModelBase::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	//継承先用
	ChildDraw();
}

//解放
void StageModelBase::Release()
{
	//継承先用
	ChildRelease();
}

