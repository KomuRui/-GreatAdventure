#pragma once
#include "PlayerState.h"

class JumpingState : public PlayerState
{
public:

	//�X�V
	void Update() override;

	//���͂ɂ���ď�ԕω�����
	void HandleInput() override;
};

