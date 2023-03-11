#pragma once
#include "../../../Stage.h"

//�X�e�[�W�N���X
class WorldStage2 : public Stage
{
	//�X�e�[�W�`�悷�邩�ǂ���
	bool isStageDraw_;

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
	/// �X�e�[�W�`�悷�邩�ǂ���
	/// </summary>
	/// <param name="flag">true�Ȃ�`�悷��</param>
	void SetStageDraw(bool flag) { isStageDraw_ = flag; }

	/// <summary>
	/// ���[�r�[�쐬
	/// </summary>
	void CreateMovie();

	/// <summary>
	/// �{�X�X�e�[�W�쐬
	/// </summary>
	void CreateBossStage();

	/// <summary>
	/// �{�X�|���V�[���쐬
	/// </summary>
	void CreateBossKill();
};

