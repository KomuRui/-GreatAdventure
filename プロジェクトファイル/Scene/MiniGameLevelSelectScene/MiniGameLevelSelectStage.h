#pragma once
#include "../../Stage.h"

//�X�e�[�W�N���X
class MiniGameLevelSelectStage : public Stage
{

public:

	//�R���X�g���N�^
	//�����Fparent
	MiniGameLevelSelectStage(GameObject* parent);

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

