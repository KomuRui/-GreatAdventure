#pragma once
#include "PlayerBase.h"

/// <summary>
/// MiniGame�p��Player
/// </summary>
class PlayerMiniGame : public PlayerBase
{

	int   hPictWind_;     //���̉摜�ԍ�
	int   hPictWind2_;    //���̉摜�ԍ�2

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e�I�u�W�F�N�g</param>
	PlayerMiniGame(GameObject* parent);


	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//������
	void ChildPlayerInitialize() override;

	//�X�^�[�g�A�b�v�f�[�g
    void ChildPlayerStartUpdate() override;

	//�X�V
	void ChildPlayerUpdate() override;

	//�`��
	void ChildDraw() override;

	//�X�e�[�W�ɍ��킹�ĉ�]
	void RotationInStage() override;

	//Player�̃J�����̏���
	void PlayerCameraBehavior(XMFLOAT3* pos, XMFLOAT3* tar) override;

	//�����蔻��
	void OnCollision(GameObject* pTarget) override;

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

	/// <summary>
	/// �������[�h�̎��̃J�����̏���
	/// </summary>
	void RunModeCameraBehavior();

};

