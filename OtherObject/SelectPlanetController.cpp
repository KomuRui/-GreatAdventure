#include "SelectPlanetController.h"
#include "../Engine/Input.h"

//���[�U�[����I������Ƃ��ɊǗ�
namespace SelectPlanetController
{
	//������(vector�̒��g����ɂ���)
	void Initialize() { PlanetInfo_.clear(); }

	//�����Z�b�g
	void SetUserPlanet(UserPlanetBase* pUserPlanet) { PlanetInfo_.push_back(pUserPlanet); }

	//�X�V����
	void Update()
	{
		//DPAD���{�^�����������Ȃ�
		if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_LEFT))
		{
			
		}
		//DPAD�E�{�^�����������Ȃ�
		else if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_LEFT))
		{

		}
	
	}
};