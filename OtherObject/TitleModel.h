#pragma once
#include "../Engine/GameObject.h"

//�^�C�g���̃��f��
class TitleModel : public GameObject
{
	////�萔

	const XMVECTOR MIN_SCALE = { 0.2,0.2,1.0 };    //�Œ�g�嗦
	const XMVECTOR MAX_SCALE = { 0.25,0.25,1.0 };  //�ō��g�嗦

	////�ϐ�

	XMVECTOR beforeScale_; //��Ԃ���O�̊g�嗦�ۑ�
	XMVECTOR targetScale_; //���̖ڕW�Ƃ���g�嗦
	int hModel_;  	       //���f���ԍ�

public:

	//�R���X�g���N�^
	TitleModel(GameObject* parent);

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
};
