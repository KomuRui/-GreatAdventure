#pragma once
#include "PlayerState.h"

class StandingState : public PlayerState
{
public:

	//�X�V
	void Update() override;

	//���͂ɂ���ď�ԕω�����
	void HandleInput() override;
};

