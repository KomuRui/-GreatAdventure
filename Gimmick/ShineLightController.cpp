#include "ShineLightController.h"
#include "../Engine/Camera.h"
#include "MoveFloor.h"
#include "../Engine/CameraTransitionObject.h"

//コンストラクタ
ShineLightController::ShineLightController(GameObject* parent)
	:GameObject(parent, "ShineLightController"),nowNumber_(0), success_(true), checkFlag_(true)
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
	else
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
bool ShineLightController::AllCheckShine()
{
	for (auto i = controller_.begin(); i != controller_.end(); i++)
	{
		//光っていなかったらfalseを返す
		if(!(*i).first->GetShineFlag())
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
			if ((*i).first->GetShineFlag())
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

		//Player動かないようにする
		GameManager::GetpPlayer()->SetAnimFlag(false);
		GameManager::GetpPlayer()->Leave();

		//カメラ動かないように
		CameraTransitionObject* pCameraTransitionObject = (CameraTransitionObject*)FindObject("CameraTransitionObject");
		pCameraTransitionObject->SetCamMoveFlag(false);

		//2.0秒後に関数を呼ぶ
		SetTimeMethod(2.0f);
	}
	//最後まで成功していないかつすべてが光っていたら
	else if(AllCheckShine() && nowNumber_ != -1)
	{
		//nowNumber_を-1にセット(初期化一度しかしないようにするため)
		ARGUMENT_INITIALIZE(nowNumber_, -1);
		
		//すべて初期の状態に戻す
		for (auto i = controller_.begin(); i != controller_.end(); i++)
		{
			(*i).first->SetNotShineLight();
			ARGUMENT_INITIALIZE((*i).second, false);
		}

		//カメラ少し振動
		Camera::SetCameraVibration(0.6f);

		//初期化
		ARGUMENT_INITIALIZE(success_, true);
		ARGUMENT_INITIALIZE(nowNumber_, ZERO);
		
	}
}

//指定した時間で呼ばれるメソッド
void ShineLightController::TimeMethod()
{
	//動くようにセット
	MoveFloor* pMoveFloor = (MoveFloor*)FindObject("MoveFloor");
	pMoveFloor->SetMove();
}

//カメラ動かす
void ShineLightController::CameraMove()
{
	//カメラのポジションとターゲットセット(補間しながら変更)
	XMVECTOR vCamPos = XMVectorLerp(XMLoadFloat3(new XMFLOAT3(Camera::GetPosition())), XMLoadFloat3(&camPos_), 0.1);
	XMVECTOR vCamTar = XMVectorLerp(XMLoadFloat3(new XMFLOAT3(Camera::GetTarget())), XMLoadFloat3(&camTar_), 0.1);
	Camera::SetPosition(Transform::VectorToFloat3(vCamPos));
	Camera::SetTarget(Transform::VectorToFloat3(vCamTar));
}