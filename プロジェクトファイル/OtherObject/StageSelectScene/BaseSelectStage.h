#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/Component/EasingMove.h"


/// <summary>
/// �X�e�[�W��I�����鎞�̃x�[�X�ƂȂ�N���X
/// </summary>
class BaseSelectStage : public GameObject
{
	//���f���ԍ�
	int hModel_;

	//�C�[�W���O�ɕK�v�ȕϐ�
	EasingMove* pEasing_;

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

