#pragma once
#include "PlayerState.h"

class RotationningState : public PlayerState
{
public:

	//�X�V
	void Update() override;

	//���͂ɂ���ď�ԕω�����
	void HandleInput() override;
};

