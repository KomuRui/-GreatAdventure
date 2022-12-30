#pragma once
#include "../Mob.h"
#include "../Engine/Model.h"

/// <summary>
/// ���C�����u�L����
/// </summary>
class MainMob : public Mob
{
	//Player�̕��������s��
	XMMATRIX toPlayer_;

	//���ł�Player�̕����������ǂ���
	bool isLookPlayer_;

	//�A�j���[�V�������邩�ǂ���
	bool isAnim_;

public:

	//�R���X�g���N�^
	MainMob(GameObject* parent, std::string modelPath, std::string name);

	//�X�V�̑O�Ɉ�x�����Ă΂��
	void ChildStartUpdate() override;

	//�X�V
	void ChildUpdate() override;

	/// <summary>
	/// Player�̕�������
	/// </summary>
	void LookPlayer();

	/// <summary>
	/// �A�j���[�V�������邩�ǂ������Z�b�g
	/// </summary>
	/// <param name="flag">true�Ȃ�A�j���[�V��������,false�Ȃ炵�Ȃ�</param>
	void SetAnim(const bool& flag) { isAnim_ = flag; }
};
