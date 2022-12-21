#include "SelectPlanetController.h"
#include "../Engine/Input.h"

//ユーザー情報を選択するときに管理
namespace SelectPlanetController
{
	//ユーザーの番号
	enum Number
	{
		First,
		Second,
		Third,
		MAX_NUAMBER
	};

	//状態
	enum Status
	{
		Stop,
		Move,
		MAX_STATUS
	};

	//各星の情報
	UserPlanetBase* planetInfo_[MAX_NUAMBER];

	//星をセット
	void SetUserPlanetFirst(UserPlanetBase* pUserPlanet) { planetInfo_[First] = pUserPlanet; }
	void SetUserPlanetSecond(UserPlanetBase* pUserPlanet) { planetInfo_[Second] = pUserPlanet; }
	void SetUserPlanetThird(UserPlanetBase* pUserPlanet) { planetInfo_[Third] = pUserPlanet; }

	//更新処理
	void Update()
	{
		//すべての星がストップしている状況かどうか
		bool stopFlag = (planetInfo_[First]->GetStatus() == Stop) && (planetInfo_[Second]->GetStatus() == Stop) && (planetInfo_[Third]->GetStatus() == Stop);

		//DPAD左ボタンを押したなら
		if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_LEFT) && stopFlag)
		{
			//各ポジション格納
			planetInfo_[First]->SetNextPosition(planetInfo_[Second]->GetPosition());
			planetInfo_[Second]->SetNextPosition(planetInfo_[Third]->GetPosition());
			planetInfo_[Third]->SetNextPosition(planetInfo_[First]->GetPosition());
		}
		//DPAD右ボタンを押したなら
		else if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_RIGHT) && stopFlag)
		{
			//各ポジション格納
			planetInfo_[First]->SetNextPosition(planetInfo_[Third]->GetPosition());
			planetInfo_[Second]->SetNextPosition(planetInfo_[First]->GetPosition());
			planetInfo_[Third]->SetNextPosition(planetInfo_[Second]->GetPosition());
		}
	
	}
};