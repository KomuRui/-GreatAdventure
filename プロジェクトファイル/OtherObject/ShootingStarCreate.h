#pragma once
#include "../Engine/GameObject/GameObject.h"

//�C�̃��f��
class ShootingStarCreate : public GameObject
{
	int hTime_; //�^�C�}�[�̃n���h��

public:

	//�R���X�g���N�^
	ShootingStarCreate(GameObject* parent);

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//������
	void Initialize() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void StartUpdate() override {};

	//�X�V
	void Update() override;

	//�`��
	void Draw() override {};

	//�J��
	void Release() override {};

	///////////////////////////�֐�//////////////////////////////

	/// <summary>
	/// ����
	/// </summary>
	void Generation();
};

