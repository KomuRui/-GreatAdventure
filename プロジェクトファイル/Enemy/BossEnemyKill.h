#pragma once
#include "../Engine/GameObject/GameObject.h"

/// <summary>
/// �{�X���|���ꂽ�V�[���p
/// </summary>
class BossEnemyKill : public GameObject
{
	
	int hModel_; //���f���ԍ�

private:

	//�R���X�g���N�^
	BossEnemyKill(GameObject* parent);

	/////////////////////�I�[�o�[���C�h����֐�///////////////////////////

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

