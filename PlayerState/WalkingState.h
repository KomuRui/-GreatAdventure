#pragma once
#include "PlayerState.h"

class WalkingState : public PlayerState
{
public:

	//�X�V
	void Update() override;

	//���͂ɂ���ď�ԕω�����
	void HandleInput() override;
};

