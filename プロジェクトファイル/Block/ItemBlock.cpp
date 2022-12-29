#include "ItemBlock.h"
#include "../Gimmick/Coin.h"

//定数
namespace
{
	static const float ADD_ROTATION_ANGLE = 0.05f; //回転するときに加算する角度
	static const int TEN_COIN_TYPE_NUM = 10;       //10コイン
}

//コンストラクタ
ItemBlock::ItemBlock(GameObject* parent, std::string modelPath, std::string name)
	: Block(parent, modelPath, name), type_(ItemBlockNormal), dropItemType_(TenCoin), coinCount_(ZERO)
{
	//エフェクト出すために必要なクラス
	pParticle_ = Instantiate<Particle>(this);
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
	data.textureFileName = "Cloud.png";
	data.position = transform_.position_;
	data.delay = 0;
	data.number = 150;
	data.lifeTime = 100;
	data.positionErr = XMFLOAT3(0.5, 0, 0.5);
	data.dir = VectorToFloat3(vNormal_);
	data.dirErr = XMFLOAT3(90, 90, 90);
	data.speed = 0.25f;
	data.speedErr = 1;
	data.accel = 0.93;
	data.size = XMFLOAT2(0.1, 0.1);
	data.sizeErr = XMFLOAT2(0.4, 0.4);
	data.scale = XMFLOAT2(0.99, 0.99);
	data.color = XMFLOAT4(1, 1, 0.1, 1);
	data.deltaColor = XMFLOAT4(0, 0, 0, 0);
	data.gravity = 0.003f;
	pParticle_->Start(data);

}