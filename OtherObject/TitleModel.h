#pragma once
#include "../Engine/GameObject.h"

//�^�C�g���̃��f��
class TitleModel : public GameObject
{
	//���f���ԍ�
	int hModel_;

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

