#pragma once
#include "State.h"

class WalkingState : public State
{
public:

	//�X�V
	void Update2D() override;

	//���͂ɂ���ď�ԕω�����
	void HandleInput() override;

	//��ԕω������Ƃ���񂾂��Ă΂��֐�
	void Enter() override;
};

