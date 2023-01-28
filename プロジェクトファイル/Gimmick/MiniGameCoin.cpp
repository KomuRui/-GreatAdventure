#include "MiniGameCoin.h"
#include "../Manager/GameManager/GameManager.h"

//コンストラクタ
MiniGameCoin::MiniGameCoin(GameObject* parent)
	:Coin(parent,"MiniGameCoin")
{
}

//更新の前に一度だけ呼ばれる関数
void MiniGameCoin::ChildCoinStartUpdate()
{
	///////////////明るさ///////////////////

	Model::SetBrightness(hModel_, 1.0f);

	//////////////////////コンポーネントの初期設定////////////////////////////////

	ARGUMENT_INITIALIZE(posture_.transform_, &transform_);
	ARGUMENT_INITIALIZE(posture_.down_, &down_);
	ARGUMENT_INITIALIZE(posture_.vNormal_, &vNormal_);
	ARGUMENT_INITIALIZE(posture_.hGroundModel_,hGroundModel_);
}

//更新
void MiniGameCoin::ChildCoinUpdate()
{
	//コンポーネントの更新を呼ぶ
	posture_.Update();

	//Playerより後ろに行ったら死亡
	if (transform_.position_.z < GameManager::GetpPlayer()->GetPosition().z - 5 && this->IsVisibled())
		KillMe();
}
