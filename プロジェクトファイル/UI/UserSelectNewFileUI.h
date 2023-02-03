#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Time.h"

//�O��`
class CreateStage;
class EasingMove;

/// <summary>
/// ���[�U�[���I���V�[���̐V�����t�@�C�����쐬���鎞��UI
/// </summary>
class UserSelectNewFileUI : public GameObject
{
	//UI�Ƃ��\������p
	CreateStage* pCreateStage_;

	//�����ꂽ���ǂ���
	bool isPush_;

public:

	//�R���X�g���N�^
	UserSelectNewFileUI(GameObject* parent);

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

	/// <summary>
	/// �����ꂽ���ǂ����Z�b�g
	/// </summary>
	/// <param name="flag">true�Ȃ牟���ꂽ</param>
	void SetPush(const bool& flag) { isPush_ = flag; Time::Reset(); }
};

