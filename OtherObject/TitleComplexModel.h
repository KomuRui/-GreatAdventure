#pragma once
#include "../Engine/GameObject.h"

//�^�C�g���̃��f��
class TitleComplexModel : public GameObject
{
	////�ϐ�

	int hModel_;  	       //���f���ԍ�

public:

	//�R���X�g���N�^
	TitleComplexModel(GameObject* parent);

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

