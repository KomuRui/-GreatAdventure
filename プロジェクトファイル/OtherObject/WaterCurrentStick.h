#pragma once
#include "../Engine/GameObject/GameObject.h"

//�����𔭐�����_
class WaterCurrentStick : public GameObject
{
	int hModel_;   			//���f���ԍ�
	int hEffect_;           //�G�t�F�N�g�ԍ�
	std::string filePath_;  //�t�@�C���̃p�X

	XMVECTOR front_;        //�O�x�N�g��

public:

	//�R���X�g���N�^
	WaterCurrentStick(GameObject* parent, std::string modelFilePath_, std::string name);

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

