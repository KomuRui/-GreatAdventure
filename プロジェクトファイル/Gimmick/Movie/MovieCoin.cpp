#include "MovieCoin.h"
#include "../../Enemy/BossEnemyMovie.h"
#include "../../Player/PlayerMovie.h"
#include "../../Manager/EffectManager/CoinEffectManager/CoinEffectManager.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/ResourceManager/Easing.h"

//�R���X�g���N�^
MovieCoin::MovieCoin(GameObject* parent)
	:Coin(parent, "MovieCoin"),isChange_(false)
{
}

//�X�V�̑O�Ɉ�x�����Ă΂��֐�
void MovieCoin::ChildCoinStartUpdate()
{
	//�ړI�n�̃|�W�V�����擾
	ARGUMENT_INITIALIZE(destinationPos_,((BossEnemyMovie*)FindObject("BossEnemyMovie"))->GetPosition());

	//�ŏ��Ɉړ�����|�W�V���������߂�
	PlayerMovie* pPlayer = ((PlayerMovie*)FindObject("Player"));
	XMFLOAT3 NextPos = Float3Add(pPlayer->GetPosition(), VectorToFloat3(pPlayer->GetNormal() * 6.0f));

	//�C�[�W���O�̏��ݒ�
	ARGUMENT_INITIALIZE(pEasing_,new EasingMove(&transform_.position_, transform_.position_, NextPos, 1.0f, Easing::InOutQuart));

	//���邳
	Model::SetBrightness(hModel_, 1.0f);
}

//�X�V
void MovieCoin::ChildCoinUpdate()
{
	//�ړ�����������
	if (pEasing_->Move())
	{
		//�`�F���W���Ă�����
		if (isChange_)
		{
			//�q�b�g�G�t�F�N�g
			CoinEffectManager::HitEffect();

			//�폜
			KillMe();
		}
		else
		{
			//���̃C�[�W���O�̏��ݒ�
			pEasing_->Reset(&transform_.position_, transform_.position_, destinationPos_, 1.0f, Easing::InOutQuart);

			//�`�F���W�����ɂ���
			ARGUMENT_INITIALIZE(isChange_, true);
		}
	}
}
