#pragma once
#include "../../../Stage.h"

//�X�e�[�W�N���X
class WorldStage2 : public Stage
{


public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	WorldStage2(GameObject* parent);

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

	/// <summary>
	/// ���[�r�[�쐬
	/// </summary>
	void CreateMovie();
};

