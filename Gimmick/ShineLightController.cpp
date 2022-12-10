#include "ShineLightController.h"
#include "../Engine/Camera.h"
#include "MoveFloor.h"

//�R���X�g���N�^
ShineLightController::ShineLightController(GameObject* parent)
	:GameObject(parent, "ShineLightController"),nowNumber_(0), success_(true), checkFlag_(true)
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
	if(checkFlag_)
		CheckinOrderShine();
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

		//�����悤�ɃZ�b�g
		MoveFloor* pMoveFloor = (MoveFloor*)FindObject("MoveFloor");
		pMoveFloor->SetMove();
	}
	//�Ō�܂Ő������Ă��Ȃ������ׂĂ������Ă�����
	else if(AllCheckShine() && nowNumber_ != -1)
	{
		//nowNumber_��-1�ɃZ�b�g(��������x�������Ȃ��悤�ɂ��邽��)
		ARGUMENT_INITIALIZE(nowNumber_, -1);
		
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
	
}
