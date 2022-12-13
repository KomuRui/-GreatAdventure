#pragma once
#include "../Stage.h"
#include "../Player.h"

//�Q�[���̂��낢��ȊǗ�������
namespace GameManager
{
	//�v���C���[�̃|�C���^�Z�b�g
	void SetpPlayer(Player* player);

	//�v���C���[�̃|�C���^�Q�b�g
	Player* GetpPlayer();

	//�X�e�[�W�̃|�C���^�Z�b�g
	void SetpStage(Stage* stage);

	//�X�e�[�W�̃|�C���^�Q�b�g
	Stage* GetpStage();

	//�t�F�[�h�`��
	void FadeDraw();

	//�t�F�[�h�C���`��
	void FadeInDraw();

	//�t�F�[�h�A�E�g�`��
	void FadeOutDraw();
};

