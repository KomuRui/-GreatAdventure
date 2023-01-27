#pragma once
#include "PlayerBase.h"

/// <summary>
/// 2D�p��Player
/// </summary>
class Player2D : public PlayerBase
{
	////2D�̍ۂ̃u���b�N�Ƃ̓����蔻��Ɏg��

	enum BlockHitTest2D
	{
		Right = 0,                            //�E
		Left,                                 //��
		Under,                                //��
		Top,                                  //��
	};

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e�I�u�W�F�N�g</param>
	Player2D(GameObject* parent);


	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//�p����p�̍X�V
	void ChildPlayerUpdate() override;

	//�X�e�[�W�ɍ��킹�ĉ�]
	void RotationInStage() override;

	//Player�̃J�����̏���
	void PlayerCameraBehavior(XMFLOAT3* pos, XMFLOAT3* tar) override;

	/////////////////////////�֐�//////////////////////////

	/// <summary>
	/// �v���C���[����
	/// </summary>
	void MovingOperation();

	/// <summary>
	/// ���C�œ����蔻��
	/// </summary>
	void StageRayCast();

	/// <summary>
	/// �����蔻��
	/// </summary>
	/// <param name="data">���C�L���X�g�̃f�[�^</param>
	/// <param name="dir">�����蔻�肷�����</param>
	void HitTest(RayCastData* data, const XMVECTOR& dir);

};

