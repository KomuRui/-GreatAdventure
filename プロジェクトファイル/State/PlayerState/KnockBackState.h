#pragma once
#include "PlayerState.h"

class PlayerBase;

/// <summary>
/// �m�b�N�o�b�N���
/// </summary>
class KnockBackState : public PlayerState
{
	//�m�b�N�o�b�N�̕����Ƌ���
	XMVECTOR knockBackDir_;

	//���ԂƂ��̌��ƂȂ��x�N�g��
	XMVECTOR vFly_;

	//���ƂȂ�t���C�x�N�g����ۑ����Ă���
	XMVECTOR keepFly_;

	//���������G�̃|�W�V����
	XMFLOAT3 hitEnemyPos_;

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

	/// <summary>
	/// ���������G�̃|�W�V�������Z�b�g
	/// </summary>
	/// <param name="pos">���������G�̃|�W�V����</param>
	void SetHitEnemyPos(const XMFLOAT3& pos) { hitEnemyPos_ = pos; }
};

