#include "ItemBlock.h"
#include "../Gimmick/Coin.h"
#include "../Engine/ResourceManager/VFX.h"

//�萔
namespace
{
	static const float ADD_ROTATION_ANGLE = 0.05f; //��]����Ƃ��ɉ��Z����p�x
	static const int TEN_COIN_TYPE_NUM = 10;       //10�R�C��
}

//�R���X�g���N�^
ItemBlock::ItemBlock(GameObject* parent, std::string modelPath, std::string name)
	: Block(parent, modelPath, name), type_(ItemBlockNormal), dropItemType_(TenCoin), coinCount_((int)ZERO)
{
}

//�X�V
void ItemBlock::BlockChildUpdate()
{
	//�����^��Rotation�Ȃ�
	if (type_ == ItemBlockRotation) Move();
}

//�u���b�N�̓���
void ItemBlock::Move()
{
	//��]������
	angle_ += ADD_ROTATION_ANGLE;
}

//�p����p��Player�������瓖���������̋���
void ItemBlock::BlockChildHitToLowerPlayer()
{
	//�h���b�v����A�C�e�����Ƃɏ����𕪂���
	switch (dropItemType_)
	{
	//�����Ȃ�
	case None:
		break;
	//�R�C���ꖇ
	case OneCoin:
	{
		//�G�t�F�N�g�\��
		HitEffect();

		//�R�C���\��
		Coin* pCoin = Instantiate<Coin>(GetParent(), "Stage/Gimmick/Coin.fbx", "Coin");
		pCoin->SetType(BlockCoinType);
		pCoin->SetPosition(transform_.position_);
		ARGUMENT_INITIALIZE(dropItemType_, None);
	}
		break;

	//�R�C��10��(1�����o�Ă���)
	case TenCoin:
	{
		//����10�ȏ�Ȃ�o�Ȃ��悤�ɕύX
		if(coinCount_ >= TEN_COIN_TYPE_NUM)
			ARGUMENT_INITIALIZE(dropItemType_, None);

		//�����܂��������Ă��Ȃ���Ԃ�������
		if (!isHit_)
		{
			//�G�t�F�N�g�\��
			HitEffect();

			//�R�C���\��
			Coin* pCoin = Instantiate<Coin>(GetParent(), "Stage/Gimmick/Coin.fbx", "Coin");
			pCoin->SetType(BlockCoinType);
			pCoin->SetPosition(transform_.position_);
			coinCount_++;
		}
	}

		break;

	//�ǂ�ł��Ȃ��Ȃ牽�����Ȃ�
	default:
		break;
	}
}

//�����������̃G�t�F�N�g
void ItemBlock::HitEffect()
{
	EmitterData data;
	data.textureFileName = "Image/Effect/Cloud.png";
	data.position = transform_.position_;
	data.delay = 0;
	data.number = 150;
	data.lifeTime = 100;
	data.positionRnd = XMFLOAT3(0.5, 0, 0.5);
	data.direction = VectorToFloat3(vNormal_);
	data.directionRnd = XMFLOAT3(90, 90, 90);
	data.speed = 0.25f;
	data.speedRnd = 1;
	data.accel = 0.93f;
	data.size = XMFLOAT2(0.1f, 0.1f);
	data.sizeRnd = XMFLOAT2(0.4f, 0.4f);
	data.scale = XMFLOAT2(0.99f, 0.99f);
	data.color = XMFLOAT4(1.0f, 1.0f, 0.1f, 1.0f);
	data.deltaColor = XMFLOAT4(0, 0, 0, 0);
	data.gravity = 0.003f;
	VFX::Start(data);

}