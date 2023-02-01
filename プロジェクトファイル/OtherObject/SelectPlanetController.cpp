#include "SelectPlanetController.h"
#include "../Engine/Input.h"
#include "../Engine/Camera.h"
#include "../Manager/GameManager/GameManager.h"
#include "../Engine/CreateStage.h"
#include "../UI/UserSelectNewFileUI.h"

//定数
namespace
{
	static const XMFLOAT3 CAM_MOVE_POS = { ZERO,ZERO,15 };  //カメラの移動位置
	static const float STATUS_CHANGE_DISTANCE = 5.0f;		//状態を変更する距離
	static const float INTERPOLATION_FACTOR = 0.01f;        //補間係数
}

//ユーザー情報を選択するときに管理
namespace SelectPlanetController
{
	//状態
	SelectPlanetStatus userSelectStatus_;

	//各星の情報
	UserPlanetBase* firstPlanetInfo_;  //1
	UserPlanetBase* secondPlanetInfo_; //2
	UserPlanetBase* thirdPlanetInfo_;  //3

	//選択している星
	UserPlanetBase* selectPlanet_;

	//星をセット
	void SetUserPlanetFirst(UserPlanetBase* pUserPlanet) { ARGUMENT_INITIALIZE(firstPlanetInfo_,pUserPlanet); }
	void SetUserPlanetSecond(UserPlanetBase* pUserPlanet) { ARGUMENT_INITIALIZE(secondPlanetInfo_,pUserPlanet); }
	void SetUserPlanetThird(UserPlanetBase* pUserPlanet) { ARGUMENT_INITIALIZE(thirdPlanetInfo_,pUserPlanet); }


	//初期化
	void Initialize()
	{
		ARGUMENT_INITIALIZE(selectPlanet_, nullptr);
		ARGUMENT_INITIALIZE(userSelectStatus_, SelectPlanetStatus::Selecting);
	}


	//更新処理
	void Update()
	{
		//状態によって分ける
		switch(userSelectStatus_)
		{
		//選択中
		case SelectPlanetStatus::Selecting:
			NowSelect();
			break;

		//選択
		case SelectPlanetStatus::Select:
			Select();
			break;

		//新規作成
		case SelectPlanetStatus::NewCreate:

			break;

		//既存
		case SelectPlanetStatus::Existing:

			break;

		//その他
		default:
			break;
		}

	}

    //選択中
	void NowSelect()
	{
		//すべての星がストップしている状況かどうか
		bool IsStop = (firstPlanetInfo_->GetStatus() == PlanetStatus::Stop) && (secondPlanetInfo_->GetStatus() == PlanetStatus::Stop) && (thirdPlanetInfo_->GetStatus() == PlanetStatus::Stop);

		//DPAD左ボタンを押したなら
		if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_LEFT) && IsStop)
		{
			//各ポジション格納
			firstPlanetInfo_->SetNextPosition(secondPlanetInfo_->GetPosition());
			secondPlanetInfo_->SetNextPosition(thirdPlanetInfo_->GetPosition());
			thirdPlanetInfo_->SetNextPosition(firstPlanetInfo_->GetPosition());
			
			//選択されているか取得
			bool first =  firstPlanetInfo_->IsSelect();
			bool second = secondPlanetInfo_->IsSelect();
			bool third =  thirdPlanetInfo_->IsSelect();

			//選択されているかどうかで次の星を選択状態に
			if (first)  thirdPlanetInfo_->SetIsSelect(true);
			if (second) firstPlanetInfo_->SetIsSelect(true);
			if (third)  secondPlanetInfo_->SetIsSelect(true);

		}
		//DPAD右ボタンを押したなら
		else if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_RIGHT) && IsStop)
		{
			//各ポジション格納
			firstPlanetInfo_->SetNextPosition(thirdPlanetInfo_->GetPosition());
			thirdPlanetInfo_->SetNextPosition(secondPlanetInfo_->GetPosition());
			secondPlanetInfo_->SetNextPosition(firstPlanetInfo_->GetPosition());

			//選択されているか取得
			bool first = firstPlanetInfo_->IsSelect();
			bool second = secondPlanetInfo_->IsSelect();
			bool third = thirdPlanetInfo_->IsSelect();

			//選択されているかどうかで次の星を選択状態に
			if (first)  secondPlanetInfo_->SetIsSelect(true);
			if (second) thirdPlanetInfo_->SetIsSelect(true);
			if (third)  firstPlanetInfo_->SetIsSelect(true);
		}

		//Aボタンを押したなら
		if (Input::IsPadButton(XINPUT_GAMEPAD_A) && IsStop)
		{
			//状態が変更できていなかったら選択されている星に入れる
			if (!firstPlanetInfo_->SetStatus(PlanetStatus::Fall))
				ARGUMENT_INITIALIZE(selectPlanet_, firstPlanetInfo_);

			//状態が変更できていなかったら選択されている星に入れる
			if (!secondPlanetInfo_->SetStatus(PlanetStatus::Fall))
				ARGUMENT_INITIALIZE(selectPlanet_, secondPlanetInfo_);

			//状態が変更できていなかったら選択されている星に入れる
			if (!thirdPlanetInfo_->SetStatus(PlanetStatus::Fall))
				ARGUMENT_INITIALIZE(selectPlanet_, thirdPlanetInfo_);

			//選択状態に
			ARGUMENT_INITIALIZE(userSelectStatus_, SelectPlanetStatus::Select);
		}

	}

	//選択
	void Select() { CameraMove(); }

	//カメラ移動
	void CameraMove(){ 

		//カメラのポジションを移動
		XMFLOAT3 pos = Camera::GetPosition();
		Camera::SetPosition(VectorToFloat3(XMVectorLerp(XMLoadFloat3(&pos),XMLoadFloat3(&CAM_MOVE_POS), INTERPOLATION_FACTOR)));
	
		//もし距離が近くなったら
		if (RangeCalculation(pos, CAM_MOVE_POS) < STATUS_CHANGE_DISTANCE)
		{
			//作成したステージ削除
			GameManager::GetpStage()->GetCreateStage()->AllCreateStageDelete();

			//選択状態に
			ARGUMENT_INITIALIZE(userSelectStatus_, SelectPlanetStatus::NewCreate);

			//次のUIを表示
			Instantiate<UserSelectNewFileUI>(GameManager::GetpStage());
		}
	}

	//ユーザー情報を選択するときの状態を取得
	SelectPlanetStatus GetStatus() { return userSelectStatus_; }
};