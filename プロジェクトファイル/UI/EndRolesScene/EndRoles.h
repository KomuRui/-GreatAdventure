#pragma once
#include "../ImageBase.h"

/// <summary>
/// �G���h���[���𗬂��N���X
/// </summary>
class EndRoles : public ImageBase
{

	//�߂�摜�ԍ�
	int hReturnImage_;

	//�߂�摜�ԍ��̃g�����X�t�H�[��
	Transform tReturnImage_;

public:


	//�R���X�g���N�^
	EndRoles(GameObject* parent, std::string modelPath, std::string name);

	//�X�V�̑O�Ɉ�x�����Ă΂��
	void ChildStartUpdate() override;

	//�X�V
	void ChildUpdate() override;

	//�`��
	void ChildDraw() override;

};

