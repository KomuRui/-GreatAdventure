#pragma once
#include "../Engine/Input.h"
#include "../Engine/Global.h"

//��Ԃ̊��N���X
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

	/// <summary>
	/// ��ԕύX
	/// </summary>
	/// <param name="nowState">���݂̏��</param>
	/// <param name="state">�ω����������</param>
	void ChangeState(State* nowState,State* state);
};
