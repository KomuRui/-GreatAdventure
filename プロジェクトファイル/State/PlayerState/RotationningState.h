#pragma once
#include "../State.h"

class RotationningState : public State
{
	int rotationCount_; //��Fps��]���Ă��邩

public:

	//�X�V
	void Update2D() override;

	//3D�p�X�V
	void Update3D() override;

	//���͂ɂ���ď�ԕω�����
	void HandleInput() override;

	//��ԕω������Ƃ���񂾂��Ă΂��֐�
	void Enter() override;
};

