#include "ItemBlock.h"
#include "../Gimmick/Coin.h"
#include "../Engine/ResourceManager/VFX.h"

//定数
namespace
{
	static const float ADD_ROTATION_ANGLE = 0.05f; //回転するときに加算する角度
	static const int TEN_COIN_TYPE_NUM = 10;       //10コイン
}

//コンストラクタ
ItemBlock::ItemBlock(GameObject* parent, std::string modelPath, std::string name)
	: Block(parent, modelPath, name), type_(ItemBlockNormal), dropItemType_(TenCoin), coinCount_((int)ZERO)
{
}

//更新
void ItemBlock::BlockChildUpdate()
{
	//もし型がRotationなら
	if (type_ == ItemBlockRotation) Move();
}

//ブロックの動き
void ItemBlock::Move()
{
	//回転させる
	angle_ += ADD_ROTATION_ANGLE;
}

//継承先用のPlayerが下から当たった時の挙動
void ItemBlock::BlockChildHitToLowerPlayer()
{
	//ドロップするアイテムごとに処理を分ける
	switch (dropItemType_)
	{
	//何もなし
	case None:
		break;
	//コイン一枚
	case OneCoin:
	{
		//エフェクト表示
		HitEffect();

		//コイン表示
		Coin* pCoin = Instantiate<Coin>(GetParent(), "Stage/Gimmick/Coin.fbx", "Coin");
		pCoin->SetType(BlockCoinType);
		pCoin->SetPosition(transform_.position_);
		ARGUMENT_INITIALIZE(dropItemType_, None);
	}
		break;

	//コイン10枚(1枚ずつ出てくる)
	case TenCoin:
	{
		//もし10以上なら出ないように変更
		if(coinCount_ >= TEN_COIN_TYPE_NUM)
			ARGUMENT_INITIALIZE(dropItemType_, None);

		//もしまだ当たっていない状態だったら
		if (!isHit_)
		{
			//エフェクト表示
			HitEffect();

			//コイン表示
			Coin* pCoin = Instantiate<Coin>(GetParent(), "Stage/Gimmick/Coin.fbx", "Coin");
			pCoin->SetType(BlockCoinType);
			pCoin->SetPosition(transform_.position_);
			coinCount_++;
		}
	}

		break;

	//どれでもないなら何もしない
	default:
		break;
	}
}

//当たった時のエフェクト
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