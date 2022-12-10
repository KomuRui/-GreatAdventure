#include "CameraTransitionObject.h"
#include "BoxCollider.h"
#include "Camera.h"
#include "GameManager.h"

//コンストラクタ
CameraTransitionObject::CameraTransitionObject(GameObject* parent, const StageCameraTransition& camInfo)
	:GameObject(parent,"CameraTransitionObject"), hitFlag(false), cameraMoveFlag_(true)
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

	//まだ当たっていないのなら
	if (!hitFlag)
	{
		//1.0秒後にメソッドを呼ぶ
		//ここではPlayer操作を新たにセットしたカメラから見た移動をさせたいので...
		//すぐ切り替えると操作しずらいので少し間をおいてから...
		SetTimeMethod(1.0f);
		ARGUMENT_INITIALIZE(hitFlag, true);
	}

	//カメラ動かすなら
	if (cameraMoveFlag_)
	{
		//カメラのポジションとターゲットセット(補間しながら変更)
		XMVECTOR vCamPos = XMVectorLerp(XMLoadFloat3(new XMFLOAT3(Camera::GetPosition())), XMLoadFloat3(&info.CameraPosition), 0.1);
		XMVECTOR vCamTar = XMVectorLerp(XMLoadFloat3(new XMFLOAT3(Camera::GetTarget())), XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())), 0.1);
		Camera::SetPosition(Transform::VectorToFloat3(vCamPos));
		Camera::SetTarget(Transform::VectorToFloat3(vCamTar));
	}
}

//当たり判定(誰とも当たっていない時)
void CameraTransitionObject::OutCollision()
{
	//当たっていたなら
	if (hitFlag)
	{
		//1.0秒後にメソッドを呼ぶ
		//ここではPlayer操作を新たにセットしたカメラから見た移動をさせたいので...
		//すぐ切り替えると操作しずらいので少し間をおいてから...
		SetTimeMethod(1.0f);

		//当たっていない状態に
		ARGUMENT_INITIALIZE(hitFlag, false);
	}
}

//指定した時間で呼ばれるメソッド
void CameraTransitionObject::TimeMethod()
{
	//カメラ動作を
	GameManager::GetpPlayer()->SetCamFlag(!(GameManager::GetpPlayer()->GetCamFlag()));
}