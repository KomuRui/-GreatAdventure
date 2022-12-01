#pragma once
#include "../../../Stage.h"

//�X�e�[�W�N���X
class WorldStage1 : public Stage
{
	//�X�e�[�W�p�̃��f��
	enum StageModel
	{
		Rotation,
		STAGE_MODEL_MAX
	};

	//���f���ԍ��i�[�p
	int Model_[STAGE_MODEL_MAX];

	//��]����I�u�W�F�N�g�p�̃g�����X�t�H�[��
	Transform tRotation_;  

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	WorldStage1(GameObject* parent);

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

