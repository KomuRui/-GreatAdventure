#pragma once
#include "State.h"

class JumpingState : public State
{
	XMVECTOR vJamp_;        //�W�����v����Ƃ��̌��ƂȂ��x�N�g��
	XMVECTOR keepJamp_;     //���ƂƂȂ�W�����v�x�N�g����ۑ����Ă���

public:

	//�X�V
	void Update() override;

	//���͂ɂ���ď�ԕω�����
	void HandleInput() override;

	//��ԕω������Ƃ���񂾂��Ă΂��֐�
	void Enter() override;
};

