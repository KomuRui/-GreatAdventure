#pragma once
#include "../../Engine/GameObject/GameObject.h"


/// <summary>
/// �X�e�[�W��I�����鎞�̃x�[�X�ƂȂ�N���X
/// </summary>
class BaseSelectStage : public GameObject
{

	//���f���ԍ�
	int hModel_;

public:

	//�R���X�g���N�^
	BaseSelectStage(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void StartUpdate() override {};

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override {};
};

