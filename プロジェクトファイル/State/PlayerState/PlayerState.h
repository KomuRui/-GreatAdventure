#pragma once
#include "../../Engine/Global.h"
#include "../../Engine/Input.h"

class Player;

//��Ԃ̊��N���X
class PlayerState
{
public:

	//2D�p�X�V
	virtual void Update2D(Player* player) {};

	//3D�p�X�V
	virtual void Update3D(Player* player) {};

	//�~�j�Q�[���p�X�V
	virtual void Update3D(Player* player) {};

	//���͂ɂ���ď�ԕω�����
	virtual void HandleInput(Player* player) {};

	//��ԕω������Ƃ���񂾂��Ă΂��֐�
	virtual void Enter(Player* player) {};

	/// <summary>
	/// ��ԕύX
	/// </summary>
	/// <param name="nowState">���݂̏��</param>
	/// <param name="state">�ω����������</param>
	void ChangeState(PlayerState* nowState,PlayerState* state);
};
