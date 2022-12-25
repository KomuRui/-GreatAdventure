#include "ShineLightController.h"
#include "../Engine/Camera.h"
#include "MoveFloor.h"
#include "../Engine/CameraTransitionObject.h"

//�萔
namespace
{
	static const float VIBRATION_INTENSITY = 0.6f;		  //�U���̋���
	static const float INTERPOLATION_COEFFICIENT = 0.05f; //��ԌW��
	static const float MOVE_FLOOR_CALLING_TIME = 2.0f;    //���𓮂������\�b�h���ĂԎ���
	static const float CAM_RESET_CALLING_TIME = 3.0f;     //�J���������Z�b�g���郁�\�b�h���ĂԎ���
}

//�R���X�g���N�^
ShineLightController::ShineLightController(GameObject* parent)
	:GameObject(parent, "ShineLightController"),nowNumber_(ZERO), success_(true), checkFlag_(true), camMove_(false),
	TimeMethodStatus_(MOVE_FLOOR), camPos_(ZERO, ZERO, ZERO), camTar_(ZERO, ZERO, ZERO)
{
}

//������
void ShineLightController::Initialize()
{
}

//�X�V�̑O�Ɉ��Ă΂��֐�
void ShineLightController::StartUpdate()
{
}

//�X�V
void ShineLightController::Update()
{
	//�������ׂ�Ȃ�
	if (checkFlag_)
		CheckinOrderShine();

	//�J�����������Ȃ�
	if(camMove_)
		CameraMove();
}

//�`��
void ShineLightController::Draw()
{
}

//���
void ShineLightController::Release()
{
}

//���ׂČ����Ă��邩���ׂ�
bool ShineLightController::IsAllShine()
{
	for (auto i = controller_.begin(); i != controller_.end(); i++)
	{
		//�����Ă��Ȃ�������false��Ԃ�
		if(!(*i).first->IsShine())
			return false;
	}

	//���ׂČ����Ă�����true�Ԃ�
	return true;
}

//���Ԓʂ���点�Ă��邩���ׂ�
void ShineLightController::CheckinOrderShine()
{
	//�������̒i�K�ŏ��Ԓʂ萬�����Ă���Ȃ�
	if (success_)
	{
		for (auto i = controller_.begin(); i != controller_.end(); i++)
		{
			//�����Ă�����true��
			if ((*i).first->IsShine())
			{
				//�����������I�u�W�F�ƍ�����Ȃ���΂����Ȃ��I�u�W�F�̃��f���p�X�l�[�����ꏏ�Ȃ炩�܂������Ă��Ȃ�������
				if ((*i).first->GetModelPathName() == (*(controller_.begin() + nowNumber_)).first->GetModelPathName() && (*i).second == false)
				{
					nowNumber_++;
					ARGUMENT_INITIALIZE((*i).second,true);
				}
				else if ((*i).second != true)
				{
					ARGUMENT_INITIALIZE(success_, false);
					ARGUMENT_INITIALIZE((*i).second, true);
				}
			}
		}
	}

	//�����Ō�܂Ő���������
	if (nowNumber_ == controller_.size())
	{
		//�������ׂȂ��悤��
		ARGUMENT_INITIALIZE(checkFlag_, false);

		//�J����������
		ARGUMENT_INITIALIZE(camMove_, true);

		//Player�����Ȃ��悤�ɂ���
		GameManager::GetpPlayer()->SetAnimFlag(false);
		GameManager::GetpPlayer()->Leave();

		//���X�����Ă����J���������Ȃ��悤��
		CameraTransitionObject* pCameraTransitionObject = (CameraTransitionObject*)FindObject("CameraTransitionObject");
		pCameraTransitionObject->SetCamMoveFlag(false);

		//2.0�b��Ɋ֐����Ă�
		SetTimeMethod(MOVE_FLOOR_CALLING_TIME);
	}
	//�Ō�܂Ő������Ă��Ȃ������ׂĂ������Ă�����
	else if(IsAllShine())
	{
		//���ׂď����̏�Ԃɖ߂�
		for (auto i = controller_.begin(); i != controller_.end(); i++)
		{
			(*i).first->SetNotShineLight();
			ARGUMENT_INITIALIZE((*i).second, false);
		}

		//�J���������U��
		Camera::SetCameraVibration(VIBRATION_INTENSITY);

		//������
		ARGUMENT_INITIALIZE(success_, true);
		ARGUMENT_INITIALIZE(nowNumber_, ZERO);
	}
}

//�w�肵�����ԂŌĂ΂�郁�\�b�h
void ShineLightController::TimeMethod()
{
	switch (TimeMethodStatus_)
	{
	//�������悤�ɃZ�b�g
	case MOVE_FLOOR:
		{
			//������
			MoveFloor* pMoveFloor = (MoveFloor*)FindObject("MoveFloor");
			pMoveFloor->SetMove();

			//��ԕύX
			ARGUMENT_INITIALIZE(TimeMethodStatus_, CAM_RESET);

			//3.0�b��Ɋ֐����Ă�
			SetTimeMethod(CAM_RESET_CALLING_TIME);

			break;
		}

	//�J������ʏ��ԂɃ��Z�b�g����
	case CAM_RESET:
		{
			//�J���������Ȃ��悤��
			ARGUMENT_INITIALIZE(camMove_, false);

			//���X�̃J���������悤��
			CameraTransitionObject* pCameraTransitionObject = (CameraTransitionObject*)FindObject("CameraTransitionObject");
			pCameraTransitionObject->SetCamMoveFlag(true);

			//Player�����悤��
			GameManager::GetpPlayer()->SetAnimFlag(true);
			GameManager::GetpPlayer()->Enter();

			break;
		}

	//�f�t�H���g�p
	default:
		break;
	}
	
}

//�J����������
void ShineLightController::CameraMove()
{
	//�J�����̃|�W�V�����ƃ^�[�Q�b�g�Z�b�g(��Ԃ��Ȃ���ύX)
	XMVECTOR vCamPos = XMVectorLerp(XMLoadFloat3(new XMFLOAT3(Camera::GetPosition())), XMLoadFloat3(&camPos_), INTERPOLATION_COEFFICIENT);
	XMVECTOR vCamTar = XMVectorLerp(XMLoadFloat3(new XMFLOAT3(Camera::GetTarget())), XMLoadFloat3(&camTar_), INTERPOLATION_COEFFICIENT);
	Camera::SetPosition(VectorToFloat3(vCamPos));
	Camera::SetTarget(VectorToFloat3(vCamTar));
}