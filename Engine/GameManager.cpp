#include "GameManager.h"

namespace GameManager
{
	///////////////////////////////�ϐ�//////////////////////////////////
	
	//���ݎg�p����Ă���v���C���[�̃|�C���^�i�[�p
	Player* pNowPlayer_;

	//���݂̎g�p����Ă���X�e�[�W�̃|�C���^�i�[�p
	Stage* pNowStage_;

	///////////////////////////////�Z�b�g�Q�b�g�֐�//////////////////////////////////
	
	//�v���C���[�̃|�C���^�Z�b�g
	void GameManager::SetpPlayer(Player* player) { pNowPlayer_ = player; }

	//�v���C���[�̃|�C���^�Q�b�g
	Player* GameManager::GetpPlayer() { return pNowPlayer_; }

	//�X�e�[�W�̃|�C���^�Z�b�g
	void GameManager::SetpStage(Stage* stage) { pNowStage_ = stage; }

	//�X�e�[�W�̃|�C���^�Q�b�g
	Stage* GameManager::GetpStage() { return pNowStage_; }

	///////////////////////////////�t�F�[�h�p�֐�////////////////////////////////////

	//�t�F�[�h�`��
	void FadeDraw() {};

	//�t�F�[�h�C���`��
	void FadeInDraw() {};

	//�t�F�[�h�A�E�g�`��
	void FadeOutDraw(){};
}