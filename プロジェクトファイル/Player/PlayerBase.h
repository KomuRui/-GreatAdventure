#pragma once
#include "../Mob.h"
#include "../Engine/GameObject.h"

/// <summary>
/// Player�̊��N���X
/// </summary>
class PlayerBase : public Mob
{

	///////////////�L�����̕K�v�ȏ��///////////////////


	XMMATRIX mPreviousAngle_;          //�W�����v���Ă���Ƃ��̉�]�s��
	float jampRotationPreviousAngle_;  //�W�����v���Ă���Ƃ��̊p�x
	float acceleration_;               //�d�͂̉����x
	bool  normalFlag_;                 //�@���𒲂ׂ邩�ǂ���

	/////////////////////�J����//////////////////////

	enum Cam
	{
		LONG,          //������
		SHORT,         //�ߋ���
		MAX_CAM_SIZE
	};

	XMVECTOR camVec_[MAX_CAM_SIZE];    //Player����J�����܂ł̋���  
	XMMATRIX camMat_;                  //�J�����̊p�x��ύX���邽�߂̃}�g���N�X

	int   camStatus_;                  //�J�����̏��
	float camAngle_;                   //�J�����̊p�x
	bool  camPosFlag_;                 //�J�����̃|�W�V�����������ǂ���
	bool  camFlag_;                    //�J�������삷�邩�ǂ���

public:

	/// <summary>
	/// Player�̏�Ԃ�\���ϐ�
	/// </summary>
	PlayerStateManager* pState_;

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e�I�u�W�F�N�g</param>
	PlayerBase(GameObject* parent);


	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//������
	void ChildInitialize() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void ChildStartUpdate() override;

	//�X�V
	void Update() override;

	//�p����p�̍X�V
	virtual void ChildPlayerUpdate() {};

	//�`��
	void ChildDraw() override {};

	//�X�e�[�W�ɍ��킹�ĉ�]
	void RotationInStage() override {};

	//�w�肵�����ԂŌĂ΂�郁�\�b�h
	void TimeMethod() override {};

	//�����蔻��
	void OnCollision(GameObject* pTarget) override {};

	///////////////////////////�֐�////////////////////////////

	/// <summary>
	/// �J�����̏���
	/// </summary>
	void CameraBehavior() {};

	/// <summary>
	/// �^���̖@���𒲂ׂăL�����̏㎲�����肷��
	/// </summary>
	void CheckUnderNormal() {};

	/////////////////////�Z�b�g�Q�b�g�֐�//////////////////////

	/// <summary>
	/// �J�����̈ʒu�𓮂������Z�b�g
	/// </summary>
	void SetCamPosNotMove() { camPosFlag_ = false; }

	/// <summary>
	/// �L���������̖@�����ׂ邩�ǂ������Z�b�g
	/// </summary>
	/// <param name="flag">���ׂ�Ȃ�true,���ׂȂ��Ȃ�false</param>
	void SetCheckNormal(const bool& flag) { normalFlag_ = flag; }

	/// <summary>
	/// �J�������삵�Ă��邩�ǂ���
	/// </summary>
	/// <returns>���삵�Ă�Ȃ�true,���ĂȂ��Ȃ�false</returns>
	bool IsCamBehavior() { return camFlag_; }

	/// <summary>
	/// Player����]���Ă��邩�ǂ���
	/// </summary>
	/// <returns>��]���Ă���Ȃ�true,���Ă��Ȃ��Ȃ�false</returns>
	bool IsRotation() { return (PlayerStateManager::playerState_ == PlayerStateManager::playerJumpRotationning_ || PlayerStateManager::playerState_ == PlayerStateManager::playerRotationning_); }

	/// <summary>
	/// �d�͂��Z�b�g
	/// </summary>
	/// <param name="acceleration">�Z�b�g�������d�͂̒l</param>
	void SetAcceleration(const float& acceleration) { acceleration_ = acceleration; }

	/// <summary>
	/// �W�����v�������̎��̊p�x�ݒ�
	/// </summary>
	/// <param name="angle">�Z�b�g�������W�����v�������̎��̊p�x</param>
	void SetJampRotationPreviousAngle(const float& angle) { jampRotationPreviousAngle_ = angle; }

	/// <summary>
	/// �W�����v���Ă鎞��Player�̉�]�}�g���N�X�Q�b�g
	/// </summary>
	/// <returns>�W�����v���Ă鎞��Player�̉�]�}�g���N�X</returns>
	XMMATRIX GetmPreviousAngle() { return mPreviousAngle_; }

	/// <summary>
	/// �J�����̊p�x�Q�b�g
	/// </summary>
	/// <returns>�J�����̊p�x</returns>
	float GetCamAngle() { return camAngle_; }

	/// <summary>
	/// �J�������삷�邩�ǂ������Z�b�g
	/// </summary>
	/// <param name="flag">true�Ȃ瓮�삳����,false�Ȃ瓮�삳���Ȃ�</param>
	void SetCamFlag(const bool& flag) { camFlag_ = flag; }

	/// <summary>
	/// �J�����̃A���O���ߋ����ɃZ�b�g
	/// </summary>
	void SetCamShort() { camStatus_ = SHORT; CameraBehavior(); }

	/// <summary>
	/// �J�����̃A���O���������ɃZ�b�g
	/// </summary>
	void SetCamLong() { camStatus_ = LONG; CameraBehavior(); }
};

