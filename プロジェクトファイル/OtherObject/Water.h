#pragma once
#include "../Engine/GameObject/GameObject.h"

//�C�̃��f��
class Water : public GameObject
{
	int hModel_;   			//���f���ԍ�
	std::string filePath_;  //�t�@�C���̃p�X

	float scroll;           //UV�X�N���[��

public:

	//�R���X�g���N�^
	Water(GameObject* parent, std::string modelFilePath_, std::string name);

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//������
	void Initialize() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void StartUpdate() override {};

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

