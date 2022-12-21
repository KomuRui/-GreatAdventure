#include "SelectPlanetController.h"
#include "../Engine/Input.h"

//ユーザー情報を選択するときに管理
namespace SelectPlanetController
{
	//初期化(vectorの中身を空にする)
	void Initialize() { PlanetInfo_.clear(); }

	//星をセット
	void SetUserPlanet(UserPlanetBase* pUserPlanet) { PlanetInfo_.push_back(pUserPlanet); }

	//更新処理
	void Update()
	{
		//DPAD左ボタンを押したなら
		if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_LEFT))
		{
			
		}
		//DPAD右ボタンを押したなら
		else if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_LEFT))
		{

		}
	
	}
};