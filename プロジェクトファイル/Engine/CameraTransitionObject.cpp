#include "CameraTransitionObject.h"
#include "BoxCollider.h"
#include "Camera.h"
#include "GameManager.h"

//定数
namespace
{
	static const float INTERPOLATION_COEFFICIENT = 0.1f; //補間係数
	static const float TIMEMETHOD_CALLING_TIME = 1.0f;   //タイムメソッドを呼ぶ時間
}

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
	BoxCollider* collision = new BoxCollider(XMFLOAT3(ZERO,ZERO, ZERO), info.CollisionSize);
	AddCollider(collision);
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
		SetTimeMethod(TIMEMETHOD_CALLING_TIME);
		ARGUMENT_INITIALIZE(hitFlag, true);
	}

	//カメラ動かすなら
	if (cameraMoveFlag_)
	{
		//カメラのポジションとターゲットセット(補間しながら変更)
		XMVECTOR vCamPos = XMVectorLerp(XMLoadFloat3(new XMFLOAT3(Camera::GetPosition())), XMLoadFloat3(&info.CameraPosition), INTERPOLATION_COEFFICIENT);
		XMVECTOR vCamTar = XMVectorLerp(XMLoadFloat3(new XMFLOAT3(Camera::GetTarget())), XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())), INTERPOLATION_COEFFICIENT);
		Camera::SetPosition(VectorToFloat3(vCamPos));
		Camera::SetTarget(VectorToFloat3(vCamTar));
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
		SetTimeMethod(TIMEMETHOD_CALLING_TIME);

		//当たっていない状態に
		ARGUMENT_INITIALIZE(hitFlag, false);
	}
}

//指定した時間で呼ばれるメソッド
void CameraTransitionObject::TimeMethod()
{
	//カメラ動作を変更
	GameManager::GetpPlayer()->SetCamFlag(!(GameManager::GetpPlayer()->IsCamBehavior()));
}