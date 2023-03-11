#pragma once
#include "../../../Engine/GameObject/GameObject.h"

//�O��`
class EasingMove;

/// <summary>
/// �{�X�o�����鎞�̌x���C���[�W
/// </summary>
class BossWarningImage : public GameObject
{

	int hWarningPict_; 	//�x���摜�ԍ�
	int hBackGround_;   //�w�i
	int hTime_;         //�^�C�}�[�ԍ�
	int sign_;          //����

	float backGroundAlpha_;     //�w�i�̓����x

	EasingMove* pEasingMove_; 	//UI���C�[�W���O�ňړ�������p

	bool isEasingChange_;       //�C�[�W���O�ύX�������ǂ���
	bool isFinish_;          	//�Ō�܂œ������I��������ǂ���

public:

	//�R���X�g���N�^
	BossWarningImage(GameObject* parent);

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

	//////////////////////////�֐�///////////////////////////

	/// <summary>
	/// �w�i�����x�̌v�Z
	/// </summary>
	void BackGroundAlphaCalc();

	/// <summary>
	/// �Ō�܂œ������I��������
	/// </summary>
	/// <returns>true�Ȃ�I����Ă���</returns>
	bool isFinish() { return isFinish_; }
};

