#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/ResourceManager/Time.h"
#include "../../Engine/ResourceManager/Text.h"

//�O��`
class CreateStage;

/// <summary>
/// ���[�U���Q�[���X�^�[�g���鎞��UI
/// </summary>
class UserGameStartUI : public GameObject
{
	//UI�Ƃ��\������p
	CreateStage* pCreateStage_;

	//�摜
	int hCoinPict_;             //�R�C���摜
	int hStagePict_;            //�X�e�[�W�摜
	int hCrossPict_;            //�~�摜

	//�e�L�X�g
	Text* pText_;			    //�R�C���̐��\������p

public:

	//�R���X�g���N�^
	UserGameStartUI(GameObject* parent);

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
	void Release() override {};
};

