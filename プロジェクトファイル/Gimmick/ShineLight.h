#pragma once
#include "../Mob.h"
#include "../Engine/GameManager.h"

/// <summary>
/// ���郉�C�g�M�~�b�N
/// </summary>
class ShineLight : public Mob
{
	//�ϐ�

	int lightNum_;        //���C�g�̔ԍ�
	bool shineFlag_;      //�����Ă��邩�ǂ���
	bool shinePermitFlag_;//����̂������邩�ǂ���

public:

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//�X�^�[�g�A�b�v�f�[�g
	void ChildStartUpdate() override;

	//���[�v�̓�����
	void ChildUpdate() override;

	//�w�肵�����ԂŌĂ΂�郁�\�b�h
	void TimeMethod() override;

	////////////////////�֐�//////////////////////
 
	//�R���X�g���N�^
	ShineLight(GameObject* parent, std::string modelPath, std::string name);

	////////////////////�Z�b�^�[�Q�b�^�[//////////////////////
	
	/// <summary>
	/// ���点�Ȃ��悤�ɃZ�b�g
	/// </summary>
	void SetNotShineLight();

	//���点�邩���点�Ȃ������Z�b�g

	/// <summary>
	/// ���点�邩���点�Ȃ������Z�b�g
	/// </summary>
	/// <param name="flag">���点��Ȃ�true,���点�Ȃ��̂Ȃ�false</param>
	void SetShineFlag(const bool& flag) { shineFlag_ = flag; }

	/// <summary>
	/// �����Ă��邩
	/// </summary>
	/// <returns>�����Ă���Ȃ�true,�����Ă��Ȃ��̂Ȃ�false</returns>
	bool IsShine() { return shineFlag_; }

};

