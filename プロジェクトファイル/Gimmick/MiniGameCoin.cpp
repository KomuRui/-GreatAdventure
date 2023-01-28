#include "MiniGameCoin.h"
#include "../Manager/GameManager/GameManager.h"

//�R���X�g���N�^
MiniGameCoin::MiniGameCoin(GameObject* parent)
	:Coin(parent,"MiniGameCoin")
{
}

//�X�V�̑O�Ɉ�x�����Ă΂��֐�
void MiniGameCoin::ChildCoinStartUpdate()
{
	///////////////���邳///////////////////

	Model::SetBrightness(hModel_, 1.0f);

	//////////////////////�R���|�[�l���g�̏����ݒ�////////////////////////////////

	ARGUMENT_INITIALIZE(posture_.transform_, &transform_);
	ARGUMENT_INITIALIZE(posture_.down_, &down_);
	ARGUMENT_INITIALIZE(posture_.vNormal_, &vNormal_);
	ARGUMENT_INITIALIZE(posture_.hGroundModel_,hGroundModel_);
}

//�X�V
void MiniGameCoin::ChildCoinUpdate()
{
	//�R���|�[�l���g�̍X�V���Ă�
	posture_.Update();

	//Player�����ɍs�����玀�S
	if (transform_.position_.z < GameManager::GetpPlayer()->GetPosition().z - 5 && this->IsVisibled())
		KillMe();
}
