#pragma once
#include "State.h"

class StandingState : public State
{
public:

	//2D�p�X�V
	void Update2D() override;

	//3D�p�X�V
	void Update3D() override;

	//���͂ɂ���ď�ԕω�����
	void HandleInput() override;

	//��ԕω������Ƃ���񂾂��Ă΂��֐�
	void Enter() override;
};

