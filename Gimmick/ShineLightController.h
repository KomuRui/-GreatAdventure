#pragma once
#include "ShineLight.h"
#include "../Engine/GameObject.h"

//���郉�C�g�M�~�b�N���R���g���[������N���X
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

	//���ׂČ����Ă��邩���ׂ�
	bool AllCheckShine(); 

	//���Ԓʂ���点�Ă��邩���ׂ�
	void CheckinOrderShine();

	//�J����������
	void CameraMove();

	////////////////////�Z�b�^�[�Q�b�^�[//////////////////////

	//���g��controller_�ɒǉ�
	void SetShineLight(ShineLight* shine) { std::pair<ShineLight*, bool> a = { shine, false }; controller_.push_back(a);  }

	//�J�����̈ʒu�ƃ^�[�Q�b�g�Z�b�g
	void SetCamPosCamTar(XMFLOAT3 pos, XMFLOAT3 tar) { camPos_ = pos; camTar_ = tar; }
};

