#include "CameraTransitionObject.h"
#include "BoxCollider.h"
#include "Camera.h"
#include "GameManager.h"

//コンストラクタ
CameraTransitionObject::CameraTransitionObject(GameObject* parent, const StageCameraTransition& camInfo)
	:GameObject(parent,"CameraTransition")
{
	//各変数初期化
	ARGUMENT_INITIALIZE(info, camInfo);
}

//初期化
void CameraTransitionObject::Initialize()
{
	//箱形の当たり判定作成
	BoxCollider* collision = new BoxCollider(XMFLOAT3(0,0,0), info.CollisionSize);
	AddCollider(collision);
}

//更新の前に一回呼ばれる関数
void CameraTransitionObject::StartUpdate()
{
}

//更新
void CameraTransitionObject::Update()
{
}

//描画
void CameraTransitionObject::Draw()
{
}

//解放
void CameraTransitionObject::Release()
{
}

//当たり判定
void CameraTransitionObject::OnCollision(GameObject* pTarget)
{
	//当たった相手がPlayer以外なら
	if (pTarget->GetObjectName() != "Player") return;

	//カメラ動作しないようにする
	GameManager::GetpPlayer()->SetCamFlag(false);

	//カメラのポジションとターゲットセット
	Camera::SetPosition(info.CameraPosition);
	Camera::SetTarget(info.CameraTarget);
}