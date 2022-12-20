#pragma once
#include "../Engine/GameObject.h"

//�^�C�g����Player���f��
class UserPlanet : public GameObject
{
	////�萔

	const float RATATION_SPEED = 0.1f;    //��]���x

	////�ϐ�

	std::string ModelNamePath_; //�t�@�C���l�[���p�X
	int hModel_; 				//���f���ԍ��i�[�p

public:

	//�R���X�g���N�^
	UserPlanet(GameObject* parent, std::string modelPath, std::string name);

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

