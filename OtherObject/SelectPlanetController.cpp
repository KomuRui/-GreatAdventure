#include "SelectPlanetController.h"
#include "../Engine/Input.h"

//���[�U�[����I������Ƃ��ɊǗ�
namespace SelectPlanetController
{
	//���[�U�[�̔ԍ�
	enum Number
	{
		First,
		Second,
		Third,
		MAX_NUAMBER
	};

	//���
	enum Status
	{
		Stop,
		Move,
		MAX_STATUS
	};

	//�e���̏��
	UserPlanetBase* planetInfo_[MAX_NUAMBER];

	//�����Z�b�g
	void SetUserPlanetFirst(UserPlanetBase* pUserPlanet) { planetInfo_[First] = pUserPlanet; }
	void SetUserPlanetSecond(UserPlanetBase* pUserPlanet) { planetInfo_[Second] = pUserPlanet; }
	void SetUserPlanetThird(UserPlanetBase* pUserPlanet) { planetInfo_[Third] = pUserPlanet; }

	//�X�V����
	void Update()
	{
		//���ׂĂ̐����X�g�b�v���Ă���󋵂��ǂ���
		bool stopFlag = (planetInfo_[First]->GetStatus() == Stop) && (planetInfo_[Second]->GetStatus() == Stop) && (planetInfo_[Third]->GetStatus() == Stop);

		//DPAD���{�^�����������Ȃ�
		if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_LEFT) && stopFlag)
		{
			//�e�|�W�V�����i�[
			planetInfo_[First]->SetNextPosition(planetInfo_[Second]->GetPosition());
			planetInfo_[Second]->SetNextPosition(planetInfo_[Third]->GetPosition());
			planetInfo_[Third]->SetNextPosition(planetInfo_[First]->GetPosition());
		}
		//DPAD�E�{�^�����������Ȃ�
		else if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_RIGHT) && stopFlag)
		{
			//�e�|�W�V�����i�[
			planetInfo_[First]->SetNextPosition(planetInfo_[Third]->GetPosition());
			planetInfo_[Second]->SetNextPosition(planetInfo_[First]->GetPosition());
			planetInfo_[Third]->SetNextPosition(planetInfo_[Second]->GetPosition());
		}
	
	}
};