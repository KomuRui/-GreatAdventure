#pragma once
#include "../Engine/GameObject.h"

/// <summary>
/// ���[�U�[���I���V�[����UI(�摜�Ƃ�����)
/// </summary>
class UserSelectSceneUI : public GameObject
{
public:

	//�R���X�g���N�^
	UserSelectSceneUI(GameObject* parent, std::string modelPath, std::string name);

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

