#pragma once
#include "../Engine/Input.h"

//Player�̏�Ԃ̊��N���X
class PlayerState
{

public:

	//�X�V
	virtual void Update() = 0;

	//���͂ɂ���ď�ԕω�����
	virtual void HandleInput() = 0;

};
