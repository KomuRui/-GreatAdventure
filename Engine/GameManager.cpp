#include "GameManager.h"

namespace GameManager
{
	//���񂴂��g�p����Ă���v���C���[�̃|�C���^�i�[�p
	Player* pNowPlayer_;

	//���݂̎g�p����Ă���X�e�[�W�̃|�C���^�i�[�p
	Stage* pNowStage_;

	//�v���C���[�̃|�C���^�Z�b�g
	void GameManager::SetpPlayer(Player* player) { pNowPlayer_ = player; }

	//�v���C���[�̃|�C���^�Q�b�g
	Player* GameManager::GetpPlayer() { return pNowPlayer_; }

	//�X�e�[�W�̃|�C���^�Z�b�g
	void GameManager::SetpStage(Stage* stage) { pNowStage_ = stage; }

	//�X�e�[�W�̃|�C���^�Q�b�g
	Stage* GameManager::GetpStage() { return pNowStage_; }
}