#pragma once
#include "StageModelBase.h"

/// <summary>
/// �X�e�[�W��I�����鎞�̂Q�Ԗڂ̃X�e�[�W
/// </summary>
class SecondStageModel : public StageModelBase
{
	//��]���郂�f���̔ԍ�
	int hRotationModel_;

	//��]���郂�f���̃g�����X�t�H�[��
	Transform tRotation_;

public:

	//�R���X�g���N�^
	SecondStageModel(GameObject* parent, std::string ModelPath, std::string name);

	//������
	void ChildInitialize() override;

	//�X�V
	void ChildUpdate()override;

	//�`��
	void ChildDraw()override;

	//�I������Ă��鎞�Ƀ{�^���������ꂽ��
	void SelectButtonPush() override;

	//�w�肵�����ԂŌĂ΂�郁�\�b�h
	void TimeMethod() override;
};

