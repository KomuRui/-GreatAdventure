#include "BossEnemyKill.h"
#include "../Engine/ResourceManager/Model.h"
#include "../Engine/GameObject/Camera.h"

//定数
namespace
{
	static const XMFLOAT3 CAM_POS = { ZERO,10,ZERO }; //カメラのポジション
}

//コンストラクタ
BossEnemyKill::BossEnemyKill(GameObject* parent)
	: GameObject(parent), hModel_(-1)
{
}

//初期化
void BossEnemyKill::Initialize()
{
	///////////////モデルデータのロード///////////////////

	hModel_ = Model::Load("Enemy/Model/MainBoss.fbx");
	assert(hModel_ >= ZERO);

	///////////////カメラの設定///////////////////

	Camera::SetPosition(CAM_POS);
	Camera::SetTarget(transform_.position_);
}

//更新
void BossEnemyKill::Update()
{


	//常にボス見るように
	Camera::SetTarget(transform_.position_);
}

//描画
void BossEnemyKill::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

