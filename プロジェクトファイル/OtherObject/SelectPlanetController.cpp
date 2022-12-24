#include "SelectPlanetController.h"
#include "../Engine/Input.h"

//���[�U�[����I������Ƃ��ɊǗ�
namespace SelectPlanetController
{
	//���
	enum Status
	{
		Stop,
		Move,
		MAX_STATUS
	};

	//�e���̏��
	UserPlanetBase* firstPlanetInfo_;  //1
	UserPlanetBase* secondPlanetInfo_; //2
	UserPlanetBase* thirdPlanetInfo_;  //3

	//�����Z�b�g
	void SetUserPlanetFirst(UserPlanetBase* pUserPlanet) { ARGUMENT_INITIALIZE(firstPlanetInfo_,pUserPlanet); }
	void SetUserPlanetSecond(UserPlanetBase* pUserPlanet) { ARGUMENT_INITIALIZE(secondPlanetInfo_,pUserPlanet); }
	void SetUserPlanetThird(UserPlanetBase* pUserPlanet) { ARGUMENT_INITIALIZE(thirdPlanetInfo_,pUserPlanet); }

	//�X�V����
	void Update()
	{
		//���ׂĂ̐����X�g�b�v���Ă���󋵂��ǂ���
		bool IsStop = (firstPlanetInfo_->GetStatus() == Stop) && (secondPlanetInfo_->GetStatus() == Stop) && (thirdPlanetInfo_->GetStatus() == Stop);

		//DPAD���{�^�����������Ȃ�
		if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_LEFT) && IsStop)
		{
			//�e�|�W�V�����i�[
			firstPlanetInfo_->SetNextPosition(secondPlanetInfo_->GetPosition());
			secondPlanetInfo_->SetNextPosition(thirdPlanetInfo_->GetPosition());
			thirdPlanetInfo_->SetNextPosition(firstPlanetInfo_->GetPosition());
		}
		//DPAD�E�{�^�����������Ȃ�
		else if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_RIGHT) && IsStop)
		{
			//�e�|�W�V�����i�[
			firstPlanetInfo_->SetNextPosition(thirdPlanetInfo_->GetPosition());
			secondPlanetInfo_->SetNextPosition(firstPlanetInfo_->GetPosition());
			thirdPlanetInfo_->SetNextPosition(secondPlanetInfo_->GetPosition());
		}
	
	}
};