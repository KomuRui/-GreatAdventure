#pragma once
#include "../ImageBase.h"

/// <summary>
/// �G���h���[���𗬂��N���X
/// </summary>
class EndRoles : public ImageBase
{

public:


	//�R���X�g���N�^
	EndRoles(GameObject* parent, std::string modelPath, std::string name);

	//�X�V�̑O�Ɉ�x�����Ă΂��
	void ChildStartUpdate() override;

	//�X�V
	void ChildUpdate() override;

};

