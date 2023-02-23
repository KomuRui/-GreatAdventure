#include "MovieCoin.h"
#include "../../Enemy/BossEnemyMovie.h"
#include "../../Player/PlayerMovie.h"
#include "../../Manager/EffectManager/CoinEffectManager/CoinEffectManager.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/ResourceManager/Easing.h"

//�萔
namespace
{
	static const float EASING_TIME = 1.0f;				//�C�[�W���O���邽�߂ɕK�v�Ȏ���
	static const float FIRST_MOVE_VALUE_RATIO = 6.0f;   //1��ڂ̈ړ����̒l�̔{��
	static const float SECOND_MOVE_VALUE_RATIO = 3.0f;  //2��ڂ̈ړ����̒l�̔{��
}

//�R���X�g���N�^
MovieCoin::MovieCoin(GameObject* parent)
	:Coin(parent, "MovieCoin"),isChange_(false)
{
}

//�X�V�̑O�Ɉ�x�����Ă΂��֐�
void MovieCoin::ChildCoinStartUpdate()
{
	//�ړI�n�̃|�W�V�������߂�
	BossEnemyMovie* pBoss = (BossEnemyMovie*)FindObject("BossEnemyMovie");
	ARGUMENT_INITIALIZE(destinationPos_, Float3Add(pBoss->GetPosition(), VectorToFloat3(pBoss->GetNormal() * SECOND_MOVE_VALUE_RATIO)));

	//�ŏ��Ɉړ�����|�W�V�������߂�
	PlayerMovie* pPlayer = ((PlayerMovie*)FindObject("Player"));
	XMFLOAT3 NextPos = Float3Add(pPlayer->GetPosition(), VectorToFloat3(pPlayer->GetNormal() * FIRST_MOVE_VALUE_RATIO));

	//�C�[�W���O�̏��ݒ�
	ARGUMENT_INITIALIZE(pEasing_,new EasingMove(&transform_.position_, transform_.position_, NextPos, EASING_TIME, Easing::InOutQuart));

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
			pEasing_->Reset(&transform_.position_, transform_.position_, destinationPos_, EASING_TIME, Easing::InOutQuart);

			//�`�F���W�����ɂ���
			ARGUMENT_INITIALIZE(isChange_, true);
		}
	}
}
