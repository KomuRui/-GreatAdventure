#include "SelectPlanetController.h"
#include "../Engine/DirectX/Input.h"
#include "../Engine/GameObject/Camera.h"
#include "../Manager/GameManager/GameManager.h"
#include "../Engine/ResourceManager/CreateStage.h"
#include "../UI/UserSelectScene/NewFileUI.h"

//�萔
namespace
{
	static const XMFLOAT3 CAM_MOVE_POS = { ZERO,ZERO,15 };  //�J�����̈ړ��ʒu
	static const float STATUS_CHANGE_DISTANCE = 5.0f;		//��Ԃ�ύX���鋗��
	static const float INTERPOLATION_FACTOR = 0.01f;        //��ԌW��
	static const float PAD_STICK_SLOPE_RIGHT = 0.8f;        //�p�b�h��L�X�e�B�b�N�̉E�̌X��
	static const float PAD_STICK_SLOPE_LEFT = -0.8f;        //�p�b�h��L�X�e�B�b�N�̍��̌X��
	static const float PAD_STICK_SLOPE_UP = 0.8f;           //�p�b�h��L�X�e�B�b�N�̏�̌X��
	static const float PAD_STICK_SLOPE_DOWN = -0.8f;        //�p�b�h��L�X�e�B�b�N�̉��̌X��

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

	//�V�K�쐬�������̑I�������A�C�R���̃��f���p�X
	std::string newCreateIconModelPath_;

	//X��Y�̑O����͕ۑ��p
	float beforeXSlope = ZERO;
	float beforeYSlope = ZERO;

	//X��Y�̌��݂̓��͕ۑ��p
	float NowXSlope = ZERO;
	float NowYSlope = ZERO;


	//�����Z�b�g
	void SetUserPlanetFirst(UserPlanetBase* pUserPlanet) { ARGUMENT_INITIALIZE(firstPlanetInfo_,pUserPlanet); }
	void SetUserPlanetSecond(UserPlanetBase* pUserPlanet) { ARGUMENT_INITIALIZE(secondPlanetInfo_,pUserPlanet); }
	void SetUserPlanetThird(UserPlanetBase* pUserPlanet) { ARGUMENT_INITIALIZE(thirdPlanetInfo_,pUserPlanet); }


	//������
	void Initialize()
	{
		ARGUMENT_INITIALIZE(newCreateIconModelPath_, "");
		ARGUMENT_INITIALIZE(selectPlanet_, nullptr);
		ARGUMENT_INITIALIZE(userSelectStatus_, SelectPlanetStatus::Selecting);
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

		//�O��̌X�����擾
		ARGUMENT_INITIALIZE(beforeXSlope, NowXSlope);
		ARGUMENT_INITIALIZE(beforeYSlope, NowYSlope);

		//PadL�X�e�B�b�N�̌X����ۑ�
		ARGUMENT_INITIALIZE(NowXSlope, Input::GetPadStickL().x);
		ARGUMENT_INITIALIZE(NowYSlope, Input::GetPadStickL().y);


		//���ɃX�e�B�b�N���X������
		if (NowXSlope <= PAD_STICK_SLOPE_LEFT && beforeXSlope >= PAD_STICK_SLOPE_LEFT && IsStop)
		{
			//�e�|�W�V�����i�[
			firstPlanetInfo_->SetNextPosition(secondPlanetInfo_->GetPosition());
			secondPlanetInfo_->SetNextPosition(thirdPlanetInfo_->GetPosition());
			thirdPlanetInfo_->SetNextPosition(firstPlanetInfo_->GetPosition());
			
			//�I������Ă��邩�擾
			bool first =  firstPlanetInfo_->IsSelect();
			bool second = secondPlanetInfo_->IsSelect();
			bool third =  thirdPlanetInfo_->IsSelect();

			//�I������Ă��邩�ǂ����Ŏ��̐���I����Ԃ�
			if (first)  thirdPlanetInfo_->SetIsSelect(true);
			if (second) firstPlanetInfo_->SetIsSelect(true);
			if (third)  secondPlanetInfo_->SetIsSelect(true);

		}
		//�E�ɃX�e�B�b�N���X������
		else if (NowXSlope >= PAD_STICK_SLOPE_RIGHT && beforeXSlope <= PAD_STICK_SLOPE_RIGHT && IsStop)
		{
			//�e�|�W�V�����i�[
			firstPlanetInfo_->SetNextPosition(thirdPlanetInfo_->GetPosition());
			thirdPlanetInfo_->SetNextPosition(secondPlanetInfo_->GetPosition());
			secondPlanetInfo_->SetNextPosition(firstPlanetInfo_->GetPosition());

			//�I������Ă��邩�擾
			bool first = firstPlanetInfo_->IsSelect();
			bool second = secondPlanetInfo_->IsSelect();
			bool third = thirdPlanetInfo_->IsSelect();

			//�I������Ă��邩�ǂ����Ŏ��̐���I����Ԃ�
			if (first)  secondPlanetInfo_->SetIsSelect(true);
			if (second) thirdPlanetInfo_->SetIsSelect(true);
			if (third)  firstPlanetInfo_->SetIsSelect(true);
		}

		//A�{�^�����������Ȃ�
		if (Input::IsPadButton(XINPUT_GAMEPAD_A) && IsStop)
		{
			//��Ԃ��ύX�ł��Ă��Ȃ�������I������Ă��鐯�ɓ����
			if (!firstPlanetInfo_->SetFallStatus())
				ARGUMENT_INITIALIZE(selectPlanet_, firstPlanetInfo_);

			//��Ԃ��ύX�ł��Ă��Ȃ�������I������Ă��鐯�ɓ����
			if (!secondPlanetInfo_->SetFallStatus())
				ARGUMENT_INITIALIZE(selectPlanet_, secondPlanetInfo_);

			//��Ԃ��ύX�ł��Ă��Ȃ�������I������Ă��鐯�ɓ����
			if (!thirdPlanetInfo_->SetFallStatus())
				ARGUMENT_INITIALIZE(selectPlanet_, thirdPlanetInfo_);

			//�I����Ԃ�
			ARGUMENT_INITIALIZE(userSelectStatus_, SelectPlanetStatus::Select);
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

	//�J�����ړ�
	void CameraMove(){ 

		//�J�����̃|�W�V�������ړ�
		XMFLOAT3 pos = Camera::GetPosition();
		Camera::SetPosition(VectorToFloat3(XMVectorLerp(XMLoadFloat3(&pos),XMLoadFloat3(&CAM_MOVE_POS), INTERPOLATION_FACTOR)));
	
		//�����������߂��Ȃ�����
		if (RangeCalculation(pos, CAM_MOVE_POS) < STATUS_CHANGE_DISTANCE)
		{
			//�쐬�����X�e�[�W�폜
			GameManager::GetpStage()->GetCreateStage()->AllCreateStageDelete();

			//�I����Ԃ�
			ARGUMENT_INITIALIZE(userSelectStatus_, SelectPlanetStatus::NewCreate);

			//����UI��\��
			Instantiate<NewFileUI>(GameManager::GetpStage());
		}
	}

	//���[�U�[����I������Ƃ��̏�Ԃ��擾
	SelectPlanetStatus GetStatus() { return userSelectStatus_; }

    //�A�C�R�����f���p�X��ݒ�
	void SetIconModelPath(std::string path) { ARGUMENT_INITIALIZE(newCreateIconModelPath_, path);  }
};