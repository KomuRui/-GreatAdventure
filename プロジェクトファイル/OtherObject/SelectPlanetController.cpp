#include "SelectPlanetController.h"
#include "../Engine/Input.h"

//ユーザー情報を選択するときに管理
namespace SelectPlanetController
{

	//各星の情報
	UserPlanetBase* firstPlanetInfo_;  //1
	UserPlanetBase* secondPlanetInfo_; //2
	UserPlanetBase* thirdPlanetInfo_;  //3

	//星をセット
	void SetUserPlanetFirst(UserPlanetBase* pUserPlanet) { ARGUMENT_INITIALIZE(firstPlanetInfo_,pUserPlanet); }
	void SetUserPlanetSecond(UserPlanetBase* pUserPlanet) { ARGUMENT_INITIALIZE(secondPlanetInfo_,pUserPlanet); }
	void SetUserPlanetThird(UserPlanetBase* pUserPlanet) { ARGUMENT_INITIALIZE(thirdPlanetInfo_,pUserPlanet); }

	//更新処理
	void Update()
	{
		//すべての星がストップしている状況かどうか
		bool IsStop = (firstPlanetInfo_->GetStatus() == PlanetStatus::Stop) && (secondPlanetInfo_->GetStatus() == PlanetStatus::Stop) && (thirdPlanetInfo_->GetStatus() == PlanetStatus::Stop);

		//DPAD左ボタンを押したなら
		if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_LEFT) && IsStop)
		{
			//各ポジション格納
			firstPlanetInfo_->SetNextPosition(secondPlanetInfo_->GetPosition());
			firstPlanetInfo_->SetIsSelect(secondPlanetInfo_->IsSelect());
			secondPlanetInfo_->SetNextPosition(thirdPlanetInfo_->GetPosition());
			secondPlanetInfo_->SetIsSelect(thirdPlanetInfo_->IsSelect());
			thirdPlanetInfo_->SetNextPosition(firstPlanetInfo_->GetPosition());
			thirdPlanetInfo_->SetIsSelect(firstPlanetInfo_->IsSelect());
		}
		//DPAD右ボタンを押したなら
		else if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_RIGHT) && IsStop)
		{
			//各ポジション格納
			firstPlanetInfo_->SetNextPosition(thirdPlanetInfo_->GetPosition());
			firstPlanetInfo_->SetIsSelect(thirdPlanetInfo_->IsSelect());
			secondPlanetInfo_->SetNextPosition(firstPlanetInfo_->GetPosition());
			secondPlanetInfo_->SetIsSelect(firstPlanetInfo_->IsSelect());
			thirdPlanetInfo_->SetNextPosition(secondPlanetInfo_->GetPosition());
			thirdPlanetInfo_->SetIsSelect(secondPlanetInfo_->IsSelect());
		}
	
		//Aボタンを押したなら
		if (Input::IsPadButton(XINPUT_GAMEPAD_A))
		{
			firstPlanetInfo_->SetStatus(PlanetStatus::Fall);
			secondPlanetInfo_->SetStatus(PlanetStatus::Fall);
			thirdPlanetInfo_->SetStatus(PlanetStatus::Fall);
		}
	}
};