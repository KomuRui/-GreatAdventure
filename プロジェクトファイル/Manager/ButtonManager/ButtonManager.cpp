#include "ButtonManager.h"
#include "../../UI/Button/ButtonBase.h"
#include "../../Engine/Global.h"
#include <vector>


//�萔
namespace
{
	static const float PAD_STICK_SLOPE_RIGHT = 0.8f;  //�p�b�h��L�X�e�B�b�N�̉E�̌X��
	static const float PAD_STICK_SLOPE_LEFT  = -0.8f; //�p�b�h��L�X�e�B�b�N�̍��̌X��
	static const float PAD_STICK_SLOPE_UP    = 0.8f;  //�p�b�h��L�X�e�B�b�N�̏�̌X��
	static const float PAD_STICK_SLOPE_DOWN  = -0.8f; //�p�b�h��L�X�e�B�b�N�̉��̌X��
}


//��ʂɕ\������Ă���{�^�����Ǘ�����
namespace ButtonManager
{

	//���ݎg���Ă���{�^�����i�[����ϐ�
	std::vector<ButtonBase*> nowUseButton;

	//X��Y�̑O����͕ۑ��p
	float beforeXSlope = ZERO;
	float beforeYSlope = ZERO;

	//X��Y�̌��݂̓��͕ۑ��p
	float NowXSlope = ZERO;
	float NowYSlope = ZERO;

	//�X�V
	void Update()
	{
		//�����{�^�����g���Ă��Ȃ������炱�̐�͏������Ȃ�
		if (nowUseButton.empty()) return;

		//�I������Ă���{�^���i�[�p
		ButtonBase* pButton = nullptr; 

		//�Ō�܂ŉ񂵂�nullptr�̂��͍̂폜�E�I������Ă���{�^����������
		for (auto i = nowUseButton.begin(); i != nowUseButton.end();)
		{
			//nullptr��������폜
			if ((*i) == nullptr)
				i = nowUseButton.erase(i);
			else
			{
				//�I������Ă�����i�[
				if ((*i)->IsSelect()) pButton = (*i);

				//���ɐi�߂�
				i++;
			}
		}

		//nullptr�Ȃ炱���ŏ����I���
		if (pButton == nullptr) return;

		//���͏���
		Input(pButton);
	}

	//����
	void Input(ButtonBase* button)
	{
		//�I������Ă���{�^����x��y��ۑ�
		float x = button->GetPosition().x;
		float y = button->GetPosition().y;

		//�O��̌X�����擾
		ARGUMENT_INITIALIZE(beforeXSlope, NowXSlope);
		ARGUMENT_INITIALIZE(beforeYSlope, NowYSlope);

		//PadL�X�e�B�b�N�̌X����ۑ�
		ARGUMENT_INITIALIZE(NowXSlope,Input::GetPadStickL().x);
		ARGUMENT_INITIALIZE(NowYSlope,Input::GetPadStickL().y);

		//�X�����萔���傫�����
		if (NowXSlope >= PAD_STICK_SLOPE_RIGHT && beforeXSlope <= PAD_STICK_SLOPE_RIGHT)
		{
			for (auto i = nowUseButton.begin(); i != nowUseButton.end(); i++)
			{
				//X�̍��W���I������Ă����{�^���������傫�����
				if ((*i)->GetPosition().x > x)
				{
					//�I������
					button->SetSelect(false);

					//X���W�ۑ�
					ARGUMENT_INITIALIZE(x, (*i)->GetPosition().x);

					//�{�^���i�[
					ARGUMENT_INITIALIZE(button, (*i));
				}
			}
		}

		//�X�����萔��菬�������
		if (NowXSlope <= PAD_STICK_SLOPE_LEFT && beforeXSlope >= PAD_STICK_SLOPE_LEFT)
		{
			for (auto i = nowUseButton.begin(); i != nowUseButton.end(); i++)
			{
				//X�̍��W���I������Ă����{�^�����������������
				if ((*i)->GetPosition().x < x)
				{
					//�I������
					button->SetSelect(false);

					//X���W�ۑ�
					ARGUMENT_INITIALIZE(x, (*i)->GetPosition().x);

					//�{�^���i�[
					ARGUMENT_INITIALIZE(button, (*i));
				}
			}
		}
				
		//�I�������悤�ɂ���
		button->SetSelect(true);
	}


	//�{�^����ǉ�
	void AddButton(ButtonBase* button) 
	{	
		//�{�^�����܂��P���o�^����Ă��Ȃ��̂Ȃ�
		if (nowUseButton.empty()) button->SetSelect(true);

		//�{�^����ǉ�
		nowUseButton.push_back(button);
	}
};