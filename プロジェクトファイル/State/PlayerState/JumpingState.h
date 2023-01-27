#pragma once
#include "PlayerState.h"

class PlayerBase;

/// <summary>
/// �W�����v���
/// </summary>
class JumpingState : public PlayerState
{
	XMVECTOR vJamp_;        //�W�����v����Ƃ��̌��ƂȂ��x�N�g��
	XMVECTOR keepJamp_;     //���ƂƂȂ�W�����v�x�N�g����ۑ����Ă���

public:

	//2D�p�X�V
	void Update2D(PlayerBase* player) override;

	//3D�p�X�V
	void Update3D(PlayerBase* player) override;

	//�~�j�Q�[���p�X�V
	void UpdateMiniGame(PlayerBase* player) override {};

	//���͂ɂ���ď�ԕω�����
	void HandleInput(PlayerBase* player) override;

	//��ԕω������Ƃ���񂾂��Ă΂��֐�
	void Enter(PlayerBase* player) override;
};

