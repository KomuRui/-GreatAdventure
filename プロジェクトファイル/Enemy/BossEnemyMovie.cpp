#include "BossEnemyMovie.h"
#include "../Manager/CoinManager/CoinManager.h"
#include "../Player/PlayerMovie.h"

//コンストラクタ
BossEnemyMovie::BossEnemyMovie(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent,"Enemy/Model/MainBoss.fbx","BossEnemyMovie"), addScaleValue_(ZERO)
{}

//初期化
void BossEnemyMovie::ChildInitialize()
{
	//コインを1個吸収した時に加算する値を設定
	ARGUMENT_INITIALIZE(addScaleValue_, 2.0f / CoinManager::GetCoinNum());

	//明るさ設定
	Model::SetBrightness(hModel_, 1.0f);
}

//更新
void BossEnemyMovie::ChildUpdate()
{
	//Playerの方を向く
	LookObject(((PlayerMovie*)FindObject("Player"))->GetPosition(), vNormal_);
}

//拡大する
void BossEnemyMovie::AddScale()
{
	ARGUMENT_INITIALIZE(transform_.scale_,Float3Add(transform_.scale_, { addScaleValue_,addScaleValue_,addScaleValue_ }));
}