#pragma once
#include "State.h"

class RotationningState : public State
{
public:

	//�X�V
	void Update() override;

	//���͂ɂ���ď�ԕω�����
	void HandleInput() override;

	//��ԕω������Ƃ���񂾂��Ă΂��֐�
	void Enter() override;
};

