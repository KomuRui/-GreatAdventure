#include "SelectPlanetController.h"
#include "../Engine/Input.h"

//ユーザー情報を選択するときに管理
namespace SelectPlanetController
{
	//状態
	enum Status
	{
		Stop,
		Move,
		MAX_STATUS
	};

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
		bool IsStop = (firstPlanetInfo_->GetStatus() == Stop) && (secondPlanetInfo_->GetStatus() == Stop) && (thirdPlanetInfo_->GetStatus() == Stop);

		//DPAD左ボタンを押したなら
		if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_LEFT) && IsStop)
		{
			//各ポジション格納
			firstPlanetInfo_->SetNextPosition(secondPlanetInfo_->GetPosition());
			secondPlanetInfo_->SetNextPosition(thirdPlanetInfo_->GetPosition());
			thirdPlanetInfo_->SetNextPosition(firstPlanetInfo_->GetPosition());
		}
		//DPAD右ボタンを押したなら
		else if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_RIGHT) && IsStop)
		{
			//各ポジション格納
			firstPlanetInfo_->SetNextPosition(thirdPlanetInfo_->GetPosition());
			secondPlanetInfo_->SetNextPosition(firstPlanetInfo_->GetPosition());
			thirdPlanetInfo_->SetNextPosition(secondPlanetInfo_->GetPosition());
		}
	
	}
};