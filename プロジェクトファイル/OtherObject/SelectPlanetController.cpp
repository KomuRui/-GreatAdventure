#include "SelectPlanetController.h"
#include "../Engine/DirectX/Input.h"
#include "../Engine/GameObject/Camera.h"
#include "../Manager/GameManager/GameManager.h"
#include "../Engine/ResourceManager/CreateStage.h"
#include "../Engine/ResourceManager/Easing.h"
#include "../Engine/Component/EasingMove.h"
#include "../UI/UserSelectScene/NewFileUI.h"
#include "../UI/UserSelectScene/UserGameStartUI.h"
#include "../Scene/UserSelectScene/UserSelectStage.h"
#include "../Manager/AudioManager/OtherAudioManager/OtherAudioManager.h"

//�萔
namespace
{
	static const XMFLOAT3 CAM_POS = { ZERO,ZERO, 5 };		//�J�����̏����ʒu
	static const XMFLOAT3 CAM_MOVE_POS = { ZERO,ZERO,15 };  //�J�����̈ړ��ʒu
	static const float STATUS_CHANGE_DISTANCE = 0.5f;		//��Ԃ�ύX���鋗��
	static const float INTERPOLATION_FACTOR = 0.01f;        //��ԌW��
}

//���[�U�[����I������Ƃ��ɊǗ�
namespace SelectPlanetController
{
	//���
	SelectPlanetStatus userSelectStatus_;

	//�e���̏��
	UserPlanetBase* firstPlanetInfo_;  //1
	UserPlanetBase* secondPlanetInfo_; //2
	UserPlanetBase* thirdPlanetInfo_;  //3

	//�I�����Ă��鐯
	UserPlanetBase* selectPlanet_;

	//�v���C���Ă��鐯�̔ԍ�
	int playPlanetNum_;

	//�C�[�W���O�p
	EasingMove* easing_;

	//�J�����̃|�W�V����
	XMFLOAT3 camPos_;

	//�V�K�쐬�������̑I�������A�C�R���̃��f���p�X
	std::string newCreateIconModelPath_;

	//�����Z�b�g
	void SetUserPlanetFirst(UserPlanetBase* pUserPlanet) { ARGUMENT_INITIALIZE(firstPlanetInfo_,pUserPlanet); }
	void SetUserPlanetSecond(UserPlanetBase* pUserPlanet) { ARGUMENT_INITIALIZE(secondPlanetInfo_,pUserPlanet); }
	void SetUserPlanetThird(UserPlanetBase* pUserPlanet) { ARGUMENT_INITIALIZE(thirdPlanetInfo_,pUserPlanet); }


	//������
	void Initialize()
	{
		ARGUMENT_INITIALIZE(playPlanetNum_, 1);
		ARGUMENT_INITIALIZE(newCreateIconModelPath_, "");
		ARGUMENT_INITIALIZE(selectPlanet_, nullptr);
		ARGUMENT_INITIALIZE(userSelectStatus_, SelectPlanetStatus::Selecting);
		ARGUMENT_INITIALIZE(easing_, new EasingMove());
		ARGUMENT_INITIALIZE(camPos_, CAM_POS);
	}

	//�X�V����
	void Update()
	{
		//��Ԃɂ���ĕ�����
		switch(userSelectStatus_)
		{
		//�I��
		case SelectPlanetStatus::Selecting:
			NowSelect();
			break;

		//�I��
		case SelectPlanetStatus::Select:
			Select();
			break;

		//�V�K�쐬
		case SelectPlanetStatus::NewCreate:
			NewCreate();
			break;

		//����
		case SelectPlanetStatus::Existing:

			break;

		//�I�𒆂ɖ߂�
		case SelectPlanetStatus::BackSelecting:
			BackSelecting();
			break;

		//���̑�
		default:
			break;
		}

	}

    //�I��
	void NowSelect()
	{
		//���ׂĂ̐����X�g�b�v���Ă���󋵂��ǂ���
		bool IsStop = (firstPlanetInfo_->GetStatus() == PlanetStatus::Stop) && (secondPlanetInfo_->GetStatus() == PlanetStatus::Stop) && (thirdPlanetInfo_->GetStatus() == PlanetStatus::Stop);

		//���ɃX�e�B�b�N���X������
		if (Input::IsPadStickLeftL() && IsStop)
		{
			//��
			OtherAudioManager::ClickAudio();

			//�e�|�W�V�����i�[
			firstPlanetInfo_->SetNextPosition(secondPlanetInfo_->GetPosition());
			secondPlanetInfo_->SetNextPosition(thirdPlanetInfo_->GetPosition());
			thirdPlanetInfo_->SetNextPosition(firstPlanetInfo_->GetPosition());
			
			//�I������Ă��邩�擾
			bool first =  firstPlanetInfo_->IsSelectToChange();
			bool second = secondPlanetInfo_->IsSelectToChange();
			bool third =  thirdPlanetInfo_->IsSelectToChange();

			//�I������Ă��邩�ǂ����Ŏ��̐���I����Ԃ�
			if (first)
			{
				thirdPlanetInfo_->SetIsSelect(true);
				ARGUMENT_INITIALIZE(playPlanetNum_, 3);
			}
			if (second)
			{
				firstPlanetInfo_->SetIsSelect(true);
				ARGUMENT_INITIALIZE(playPlanetNum_, 1);
			}
			if (third)
			{
				secondPlanetInfo_->SetIsSelect(true);
				ARGUMENT_INITIALIZE(playPlanetNum_, 2);
			}

		}
		//�E�ɃX�e�B�b�N���X������
		else if (Input::IsPadStickRightL() && IsStop)
		{
			//��
			OtherAudioManager::ClickAudio();

			//�e�|�W�V�����i�[
			firstPlanetInfo_->SetNextPosition(thirdPlanetInfo_->GetPosition());
			thirdPlanetInfo_->SetNextPosition(secondPlanetInfo_->GetPosition());
			secondPlanetInfo_->SetNextPosition(firstPlanetInfo_->GetPosition());

			//�I������Ă��邩�擾
			bool first = firstPlanetInfo_->IsSelectToChange();
			bool second = secondPlanetInfo_->IsSelectToChange();
			bool third = thirdPlanetInfo_->IsSelectToChange();

			//�I������Ă��邩�ǂ����Ŏ��̐���I����Ԃ�
			if (first)
			{
				secondPlanetInfo_->SetIsSelect(true);
				ARGUMENT_INITIALIZE(playPlanetNum_, 2);
			}
			if (second)
			{
				thirdPlanetInfo_->SetIsSelect(true);
				ARGUMENT_INITIALIZE(playPlanetNum_, 3);
			}
			if (third)
			{
				firstPlanetInfo_->SetIsSelect(true);
				ARGUMENT_INITIALIZE(playPlanetNum_, 1);
			}
		}

		//A�{�^�����������Ȃ�
		if (Input::IsPadButton(XINPUT_GAMEPAD_A) && IsStop)
		{
			//��
			OtherAudioManager::ClickAudio();

			//��Ԃ��ύX�ł��Ă��Ȃ�������I������Ă��鐯�ɓ����
			if (!firstPlanetInfo_->SetFallStatus())
			{
				ARGUMENT_INITIALIZE(selectPlanet_, firstPlanetInfo_);
				ARGUMENT_INITIALIZE(playPlanetNum_, 1);
			}

			//��Ԃ��ύX�ł��Ă��Ȃ�������I������Ă��鐯�ɓ����
			if (!secondPlanetInfo_->SetFallStatus())
			{
				ARGUMENT_INITIALIZE(selectPlanet_, secondPlanetInfo_);
				ARGUMENT_INITIALIZE(playPlanetNum_, 2);
			}

			//��Ԃ��ύX�ł��Ă��Ȃ�������I������Ă��鐯�ɓ����
			if (!thirdPlanetInfo_->SetFallStatus())
			{
				ARGUMENT_INITIALIZE(selectPlanet_, thirdPlanetInfo_);
				ARGUMENT_INITIALIZE(playPlanetNum_, 3);
			}

			//�I����Ԃ�
			ARGUMENT_INITIALIZE(userSelectStatus_, SelectPlanetStatus::Select);
			easing_->Reset(&camPos_, CAM_POS, CAM_MOVE_POS, 2.0f, Easing::OutQuart);
		}

	}

	//�I��
	void Select() { CameraMove(); }

	//�V�K�쐬
	void NewCreate()
	{
		//������񂪂Ȃ��̂Ȃ炱�̐揈�����Ȃ�
		if (newCreateIconModelPath_ == "") return;

		//�I������Ă鐯�̏�Ԃ�ύX
		selectPlanet_->SetStatus(PlanetStatus::Explosion, newCreateIconModelPath_);

		//�V�K�쐬
		selectPlanet_->CreateNewFile();

		//���[�U�[�I����Ԃ������ɕύX
		ARGUMENT_INITIALIZE(userSelectStatus_, SelectPlanetStatus::Existing);
	}

	//����
	void Existing()
	{

	}

	//�I�𒆂ɖ߂�
	void BackSelecting()
	{
		//�J�����̃|�W�V�������ړ�
		easing_->Move();
		Camera::SetPosition(camPos_);

		//�����������߂��Ȃ�����
		if (RangeCalculation(camPos_, CAM_POS) < STATUS_CHANGE_DISTANCE)
		{
			//UI��\��
			((UserSelectStage*)GameManager::GetpStage())->CreateStageUI();

			//�I�𒆏�Ԃ�
			ARGUMENT_INITIALIZE(userSelectStatus_, SelectPlanetStatus::Selecting);
		}
	}

	//�v���C���Ă��鐯�̔ԍ����擾
	int GetPlayPlanetNum() { return playPlanetNum_; }

	//�J�����ړ�
	void CameraMove(){ 

		//�J�����̃|�W�V�������ړ�
		easing_->Move();
		Camera::SetPosition(camPos_);

		//�����������߂��Ȃ�����
		if (RangeCalculation(camPos_, CAM_MOVE_POS) < STATUS_CHANGE_DISTANCE)
		{
			//�쐬�����X�e�[�W�폜
			GameManager::GetpStage()->GetCreateStage()->AllCreateStageDelete();

			//�����t�@�C���Ȃ�
			if (selectPlanet_->IsExisting())
			{
				//������Ԃ�
				ARGUMENT_INITIALIZE(userSelectStatus_, SelectPlanetStatus::Existing);

				//����UI��\��
				Instantiate<UserGameStartUI>(GameManager::GetpStage());
			}
			//�V�K�쐬�Ȃ�
			else
			{
				//�V�K�쐬��Ԃ�
				ARGUMENT_INITIALIZE(userSelectStatus_, SelectPlanetStatus::NewCreate);

				//����UI��\��
				Instantiate<NewFileUI>(GameManager::GetpStage());
			}

			//�C�[�W���O���Z�b�g
			easing_->Reset(&camPos_, CAM_MOVE_POS, CAM_POS, 2.0f, Easing::OutQuart);
		}
	}

	//���̈ړ������Z�b�g
	void ResetPlanetMove()
	{
		if (!firstPlanetInfo_->IsSelect())
		{
			firstPlanetInfo_->SetStatus(PlanetStatus::ReturnPosition);
			firstPlanetInfo_->SetReturnEasingMove();
		}
		if (!secondPlanetInfo_->IsSelect())
		{
			secondPlanetInfo_->SetStatus(PlanetStatus::ReturnPosition);
			secondPlanetInfo_->SetReturnEasingMove();
		}
		if (!thirdPlanetInfo_->IsSelect())
		{
			thirdPlanetInfo_->SetStatus(PlanetStatus::ReturnPosition);
			thirdPlanetInfo_->SetReturnEasingMove();
		}
	}

	//���[�U�[����I������Ƃ��̏�Ԃ��擾
	SelectPlanetStatus GetStatus() { return userSelectStatus_; }

	//���[�U�[����I������Ƃ��̏�Ԃ��Z�b�g
	void SetStatus(SelectPlanetStatus status) { ARGUMENT_INITIALIZE(userSelectStatus_,status); }

    //�A�C�R�����f���p�X��ݒ�
	void SetIconModelPath(std::string path) { ARGUMENT_INITIALIZE(newCreateIconModelPath_, path);  }
};