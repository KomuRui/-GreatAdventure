#include "ShineLightController.h"
#include "../Engine/GameObject/Camera.h"
#include "MoveFloor.h"
#include "../Engine/GameObject/CameraTransitionObject.h"

//定数
namespace
{
	static const float VIBRATION_INTENSITY = 0.6f;		  //振動の強さ
	static const float INTERPOLATION_COEFFICIENT = 0.05f; //補間係数
	static const float MOVE_FLOOR_CALLING_TIME = 2.0f;    //床を動かすメソッドを呼ぶ時間
	static const float CAM_RESET_CALLING_TIME = 3.0f;     //カメラをリセットするメソッドを呼ぶ時間
}

//コンストラクタ
ShineLightController::ShineLightController(GameObject* parent)
	:GameObject(parent, "ShineLightController"),nowNumber_((int)ZERO), success_(true), checkFlag_(true), camMove_(false),
	TimeMethodStatus_(MOVE_FLOOR), camPos_(ZERO, ZERO, ZERO), camTar_(ZERO, ZERO, ZERO)
{
}

//初期化
void ShineLightController::Initialize()
{
}

//更新の前に一回呼ばれる関数
void ShineLightController::StartUpdate()
{
}

//更新
void ShineLightController::Update()
{
	//もし調べるなら
	if (checkFlag_)
		CheckinOrderShine();

	//カメラ動かすなら
	if(camMove_)
		CameraMove();
}

//描画
void ShineLightController::Draw()
{
}

//解放
void ShineLightController::Release()
{
}

//すべて光っているか調べる
bool ShineLightController::IsAllShine()
{
	for (auto i = controller_.begin(); i != controller_.end(); i++)
	{
		//光っていなかったらfalseを返す
		if(!(*i).first->IsShine())
			return false;
	}

	//すべて光っていたらtrue返す
	return true;
}

//順番通り光らせているか調べる
void ShineLightController::CheckinOrderShine()
{
	//もし今の段階で順番通り成功しているなら
	if (success_)
	{
		for (auto i = controller_.begin(); i != controller_.end(); i++)
		{
			//光っていたらtrueに
			if ((*i).first->IsShine())
			{
				//もし光ったオブジェと今光らなければいけないオブジェのモデルパスネームが一緒ならかつまだ光っていなかったら
				if ((*i).first->GetModelPathName() == (*(controller_.begin() + nowNumber_)).first->GetModelPathName() && (*i).second == false)
				{
					nowNumber_++;
					ARGUMENT_INITIALIZE((*i).second,true);
				}
				else if ((*i).second != true)
				{
					ARGUMENT_INITIALIZE(success_, false);
					ARGUMENT_INITIALIZE((*i).second, true);
				}
			}
		}
	}

	//もし最後まで成功したら
	if (nowNumber_ == controller_.size())
	{
		//もう調べないように
		ARGUMENT_INITIALIZE(checkFlag_, false);

		//カメラ動かす
		ARGUMENT_INITIALIZE(camMove_, true);

		//Player動かないようにする
		GameManager::GetpPlayer()->SetAnimFlag(false);
		GameManager::GetpPlayer()->Leave();

		//元々動いていたカメラ動かないように
		CameraTransitionObject* pCameraTransitionObject = (CameraTransitionObject*)FindObject("CameraTransitionObject");
		pCameraTransitionObject->SetCamMoveFlag(false);

		//2.0秒後に関数を呼ぶ
		SetTimeMethod(MOVE_FLOOR_CALLING_TIME);
	}
	//最後まで成功していないかつすべてが光っていたら
	else if(IsAllShine())
	{
		//すべて初期の状態に戻す
		for (auto i = controller_.begin(); i != controller_.end(); i++)
		{
			(*i).first->SetNotShineLight();
			ARGUMENT_INITIALIZE((*i).second, false);
		}

		//カメラ少し振動
		Camera::SetCameraVibration(VIBRATION_INTENSITY);

		//初期化
		ARGUMENT_INITIALIZE(success_, true);
		ARGUMENT_INITIALIZE(nowNumber_, (int)ZERO);
	}
}

//指定した時間で呼ばれるメソッド
void ShineLightController::TimeMethod()
{
	switch (TimeMethodStatus_)
	{
	//床動くようにセット
	case MOVE_FLOOR:
		{
			//床動く
			MoveFloor* pMoveFloor = (MoveFloor*)FindObject("MoveFloor");
			pMoveFloor->SetMove();

			//状態変更
			ARGUMENT_INITIALIZE(TimeMethodStatus_, CAM_RESET);

			//3.0秒後に関数を呼ぶ
			SetTimeMethod(CAM_RESET_CALLING_TIME);

			break;
		}

	//カメラを通常状態にリセットする
	case CAM_RESET:
		{
			//カメラ動かないように
			ARGUMENT_INITIALIZE(camMove_, false);

			//元々のカメラ動くように
			CameraTransitionObject* pCameraTransitionObject = (CameraTransitionObject*)FindObject("CameraTransitionObject");
			pCameraTransitionObject->SetCamMoveFlag(true);

			//Player動くように
			GameManager::GetpPlayer()->SetAnimFlag(true);
			GameManager::GetpPlayer()->Enter();

			break;
		}

	//デフォルト用
	default:
		break;
	}
	
}

//カメラ動かす
void ShineLightController::CameraMove()
{
	//カメラのポジションとターゲットセット(補間しながら変更)
	XMVECTOR vCamPos = XMVectorLerp(XMLoadFloat3(new XMFLOAT3(Camera::GetPosition())), XMLoadFloat3(&camPos_), INTERPOLATION_COEFFICIENT);
	XMVECTOR vCamTar = XMVectorLerp(XMLoadFloat3(new XMFLOAT3(Camera::GetTarget())), XMLoadFloat3(&camTar_), INTERPOLATION_COEFFICIENT);
	Camera::SetPosition(VectorToFloat3(vCamPos));
	Camera::SetTarget(VectorToFloat3(vCamTar));
}