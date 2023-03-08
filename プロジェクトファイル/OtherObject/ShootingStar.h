#pragma once
#include "../Engine/GameObject/GameObject.h"
#include "../Engine/GameObject/PolyLine.h"

//�C�̃��f��
class ShootingStar : public GameObject
{
	int hModel_;   			//���f���ԍ�
	std::string filePath_;  //�t�@�C���̃p�X
	PolyLine* pBaseLine_;   //���[�v�̃��C���G�t�F�N�g

public:

	//�R���X�g���N�^
	ShootingStar(GameObject* parent, std::string modelFilePath_, std::string name);

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

