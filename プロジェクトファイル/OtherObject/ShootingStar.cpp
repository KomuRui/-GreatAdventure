#include "ShootingStar.h"
#include "../Engine/ResourceManager/Model.h"
#include "../Engine/ResourceManager/VFX.h"

//定数
namespace
{
	static const XMFLOAT3 MOVE_ADD_VALUE = { 0.3f,0.2f,0.3f };
	static const float ROTATION_ADD_VALUE = 5.5f;
	static const float KILL_POSY_VALUE = -10;
}

//コンストラクタ
ShootingStar::ShootingStar(GameObject* parent, std::string modelFilePath_, std::string name)
	:GameObject(parent, name), hModel_(-1), filePath_(modelFilePath_)
{
}

ShootingStar::ShootingStar(GameObject* parent)
	:GameObject(parent,"ShootingStar"), hModel_(-1), filePath_("Stage/Last/SootingStar.fbx")
{
}

//初期化
void ShootingStar::Initialize()
{
	//モデルデータのロード
	hModel_ = Model::Load(filePath_);
	assert(hModel_ >= ZERO);

	//明るさ変更
	Model::SetBrightness(hModel_, 1.0f);

	//テクスチャロード
	ARGUMENT_INITIALIZE(pBaseLine_,new PolyLine);
	pBaseLine_->Load("Image/Effect/tex.png");

	//各ポジション初期化
	pBaseLine_->AddPosition(transform_.position_);
	pBaseLine_->SetColor({ 1,1,ZERO });
	pBaseLine_->SetLengh(80);
}

//更新
void ShootingStar::Update()
{
	//移動
	ARGUMENT_INITIALIZE(transform_.position_,SubTract(transform_.position_, MOVE_ADD_VALUE));

	//回転
	transform_.rotate_.y += ROTATION_ADD_VALUE;

	//ポジション追加
	pBaseLine_->AddPosition(transform_.position_);

	//ポジションが定数値よりも小さければ削除
	if (transform_.position_.y < KILL_POSY_VALUE)KillMe();
}

//描画
void ShootingStar::Draw()
{
	//モデル描画
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	//ポリラインを描画
	pBaseLine_->Draw();
}

//解放
void ShootingStar::Release()
{
	SAFE_RELEASE(pBaseLine_);
	SAFE_DELETE_ARRAY(pBaseLine_);
}
