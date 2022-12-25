#pragma once
#include "ShineLight.h"
#include "../Engine/GameObject.h"

/// <summary>
/// ���郉�C�g�M�~�b�N���Ǘ�����N���X
/// </summary>
class ShineLightController : public GameObject
{
	//���郉�C�g�����ׂĕۊǂ��Ă����ϐ�(���:���C�g�̃I�u�W�F�N�g,���:�����Ă��邩�ǂ���)
	std::vector<std::pair<ShineLight*,bool>> controller_;

	//�M�~�b�N�����������Ƃ��Ɏg���J�����̈ʒu�ƃ^�[�Q�b�g
	XMFLOAT3 camPos_;
	XMFLOAT3 camTar_;
	
	//�����Ԗڂ����Ă��邩
	int nowNumber_;

	//���Ԓʂ�Ɍ��点�邱�Ƃ��o������
	bool success_;

	//���ׂ邩�ǂ���
	bool checkFlag_;

	//�J�������������ǂ���
	bool camMove_;

	//�w�肵�����ԂŊ֐����ĂԎ��ɂǂ̊֐��ĂԂ����߂��
	enum TimeMethodStatus
	{
		MOVE_FLOOR,
		CAM_RESET
	};

	//�w�肵�����ԂŊ֐����ĂԎ��ɂǂ̊֐��ĂԂ����߂�p�̏��
	int TimeMethodStatus_;


public:

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//������
	void Initialize() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void StartUpdate() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�w�肵�����ԂŌĂ΂�郁�\�b�h
	void TimeMethod() override;

	////////////////////�֐�//////////////////////

	//�R���X�g���N�^
	ShineLightController(GameObject* parent);

	/// <summary>
	/// ���ׂČ����Ă��邩�ǂ���
	/// </summary>
	/// <returns>�����Ă���Ȃ�true,��ł������Ă��Ȃ��Ȃ�false</returns>
	bool IsAllShine(); 

	/// <summary>
	/// ���Ԓʂ���点�Ă��邩���ׂ�
	/// </summary>
	void CheckinOrderShine();

	/// <summary>
	/// �J�����𓮂���
	/// </summary>
	void CameraMove();

	////////////////////�Z�b�^�[�Q�b�^�[//////////////////////

	/// <summary>
	/// ���g�̃R���g���[���[�ɃZ�b�g
	/// </summary>
	/// <param name="shine">�Z�b�g������ShineLight�̃|�C���^</param>
	void SetShineLight(ShineLight* shine) { std::pair<ShineLight*, bool> a = { shine, false }; controller_.push_back(a);  }

	/// <summary>
	/// �J�����̈ʒu�ƃJ�����̃^�[�Q�b�g�Z�b�g
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="tar">�^�[�Q�b�g</param>
	void SetCamPosCamTar(XMFLOAT3 pos, XMFLOAT3 tar) { camPos_ = pos; camTar_ = tar; }
};

