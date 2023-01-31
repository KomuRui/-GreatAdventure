#include "SelectPlanetController.h"
#include "../Engine/Input.h"

//���[�U�[����I������Ƃ��ɊǗ�
namespace SelectPlanetController
{

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
		bool IsStop = (firstPlanetInfo_->GetStatus() == PlanetStatus::Stop) && (secondPlanetInfo_->GetStatus() == PlanetStatus::Stop) && (thirdPlanetInfo_->GetStatus() == PlanetStatus::Stop);

		//DPAD���{�^�����������Ȃ�
		if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_LEFT) && IsStop)
		{
			//�e�|�W�V�����i�[
			firstPlanetInfo_->SetNextPosition(secondPlanetInfo_->GetPosition());
			firstPlanetInfo_->SetIsSelect(secondPlanetInfo_->IsSelect());
			secondPlanetInfo_->SetNextPosition(thirdPlanetInfo_->GetPosition());
			secondPlanetInfo_->SetIsSelect(thirdPlanetInfo_->IsSelect());
			thirdPlanetInfo_->SetNextPosition(firstPlanetInfo_->GetPosition());
			thirdPlanetInfo_->SetIsSelect(firstPlanetInfo_->IsSelect());
		}
		//DPAD�E�{�^�����������Ȃ�
		else if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_RIGHT) && IsStop)
		{
			//�e�|�W�V�����i�[
			firstPlanetInfo_->SetNextPosition(thirdPlanetInfo_->GetPosition());
			firstPlanetInfo_->SetIsSelect(thirdPlanetInfo_->IsSelect());
			secondPlanetInfo_->SetNextPosition(firstPlanetInfo_->GetPosition());
			secondPlanetInfo_->SetIsSelect(firstPlanetInfo_->IsSelect());
			thirdPlanetInfo_->SetNextPosition(secondPlanetInfo_->GetPosition());
			thirdPlanetInfo_->SetIsSelect(secondPlanetInfo_->IsSelect());
		}
	
		//A�{�^�����������Ȃ�
		if (Input::IsPadButton(XINPUT_GAMEPAD_A))
		{
			firstPlanetInfo_->SetStatus(PlanetStatus::Fall);
			secondPlanetInfo_->SetStatus(PlanetStatus::Fall);
			thirdPlanetInfo_->SetStatus(PlanetStatus::Fall);
		}
	}
};