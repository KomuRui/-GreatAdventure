#pragma once
#include "../Engine/GameObject.h"

//�^�C�g���̃��f��
class TitleComplexModel : public GameObject
{
	////�萔

	const float SPEED = 0.1f;
	const float VIBRATION_INTENSITY = 0.4f;
	const float LIMIT_Y = -20.0f;

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

