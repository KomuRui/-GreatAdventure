#pragma once
#include "../Mob/Mob.h"

/// <summary>
/// ����p��Player
/// </summary>
class PlayerMovie : public Mob
{
	//���[�r�[�p�̃J�����̃x�N�g��
	XMVECTOR vMovieCam_;

public:

	//�R���X�g���N�^
	PlayerMovie(GameObject* parent, std::string modelPath, std::string name);

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////
	
	//������
	void ChildInitialize() override;

	//�X�V
	void ChildUpdate() override;

	//�̃J�����̏���
	void CameraBehavior();

};

