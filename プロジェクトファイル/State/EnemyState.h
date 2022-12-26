#pragma once
#include "../Engine/Input.h"
#include "../Engine/Global.h"

//�O��`
class Enemy;

//��Ԃ̊��N���X
class EnemyState
{
public:

	/// <summary>
	/// 2D�p�X�V
	/// </summary>
	/// <param name="enemy">��Ԃ��g���Ă�G�̃|�C���^</param>
	virtual void Update2D(Enemy* enemy) = 0;

	/// <summary>
	/// 3D�p�X�V
	/// </summary>
	/// <param name="enemy">��Ԃ��g���Ă�G�̃|�C���^</param>
	virtual void Update3D(Enemy* enemy) = 0;

	/// <summary>
	/// ���͂ɂ���ď�ԕω�����
	/// </summary>
	/// <param name="enemy">��Ԃ��g���Ă�G�̃|�C���^</param>
	virtual void HandleInput(Enemy* enemy) = 0;

	/// <summary>
	/// ��ԕω������Ƃ���񂾂��Ă΂��֐�
	/// </summary>
	/// <param name="enemy">��Ԃ��g���Ă�G�̃|�C���^</param>
	virtual void Enter(Enemy* enemy) = 0;
};
