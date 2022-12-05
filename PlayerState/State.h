#pragma once
#include "../Engine/Input.h"

//Player�̏�Ԃ̊��N���X
class State
{
public:

	//2D�p�X�V
	virtual void Update2D() = 0;

	//3D�p�X�V
	virtual void Update3D() = 0;

	//���͂ɂ���ď�ԕω�����
	virtual void HandleInput() = 0;

	//��ԕω������Ƃ���񂾂��Ă΂��֐�
	virtual void Enter() = 0;

};
