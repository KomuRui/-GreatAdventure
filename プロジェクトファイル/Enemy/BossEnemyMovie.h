#pragma once
#include "../Mob/Mob.h"
#include "../UI/TalkImage.h"

/// <summary>
/// ����p�̃{�X�̓G
/// </summary>
class BossEnemyMovie : public Mob
{
	//�b���摜
	TalkImage* pTalkImage_;

	//���y
	int hAudio_;

	//���Z����l
	float addScaleValue_;

	//��b��ύX���Ă��邩
	bool isChangeTalk_;

public:

	//�R���X�g���N�^
	BossEnemyMovie(GameObject*parent, std::string modelPath, std::string name);

	//�f�X�g���N�^
	~BossEnemyMovie();

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//������
	void ChildInitialize() override;

	//�X�V
	void ChildUpdate() override;

	/////////////////////�֐�//////////////////////

	//�g�傷��
	void AddScale();
};

