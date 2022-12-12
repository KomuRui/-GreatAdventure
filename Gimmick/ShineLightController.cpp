#include "ShineLightController.h"
#include "../Engine/Camera.h"
#include "MoveFloor.h"
#include "../Engine/CameraTransitionObject.h"

//�R���X�g���N�^
ShineLightController::ShineLightController(GameObject* parent)
	:GameObject(parent, "ShineLightController"),nowNumber_(0), success_(true), checkFlag_(true), TimeMethodStatus_(MOVE_FLOOR), camMove_(false)
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
bool ShineLightController::AllCheckShine()
{
	for (auto i = controller_.begin(); i != controller_.end(); i++)
	{
		//�����Ă��Ȃ�������false��Ԃ�
		if(!(*i).first->GetShineFlag())
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
			if ((*i).first->GetShineFlag())
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
		SetTimeMethod(2.0f);
	}
	//�Ō�܂Ő������Ă��Ȃ������ׂĂ������Ă�����
	else if(AllCheckShine())
	{
		//���ׂď����̏�Ԃɖ߂�
		for (auto i = controller_.begin(); i != controller_.end(); i++)
		{
			(*i).first->SetNotShineLight();
			ARGUMENT_INITIALIZE((*i).second, false);
		}

		//�J���������U��
		Camera::SetCameraVibration(0.6f);

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
			SetTimeMethod(3.0f);

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
	XMVECTOR vCamPos = XMVectorLerp(XMLoadFloat3(new XMFLOAT3(Camera::GetPosition())), XMLoadFloat3(&camPos_), 0.05);
	XMVECTOR vCamTar = XMVectorLerp(XMLoadFloat3(new XMFLOAT3(Camera::GetTarget())), XMLoadFloat3(&camTar_), 0.05);
	Camera::SetPosition(Transform::VectorToFloat3(vCamPos));
	Camera::SetTarget(Transform::VectorToFloat3(vCamTar));
}