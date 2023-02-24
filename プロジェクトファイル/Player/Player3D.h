#pragma once
#include "PlayerBase.h"

/// <summary>
/// 3D�p��Player
/// </summary>
class Player3D : public PlayerBase
{

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e�I�u�W�F�N�g</param>
	Player3D(GameObject* parent);
	Player3D(GameObject* parent, std::string modelPath, std::string name);


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

