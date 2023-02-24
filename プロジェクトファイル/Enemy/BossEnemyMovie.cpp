#include "BossEnemyMovie.h"
#include "../Manager/CoinManager/CoinManager.h"
#include "../Player/PlayerMovie.h"

//定数
namespace
{
	//最大サイズ
	static const float MAX_SIZE = 3.0f;
}


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

	//話している時の画像・テキスト表示
	ARGUMENT_INITIALIZE(pTalkImage_, Instantiate<TalkImage>(GetParent()->GetParent()->GetParent()));
	pTalkImage_->NewCsvFile("Stage/World/World2/MobTalk_Movie.csv");
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
	//拡大
	ARGUMENT_INITIALIZE(transform_.scale_,Float3Add(transform_.scale_, { addScaleValue_,addScaleValue_,addScaleValue_ }));

	//もし最大サイズになったら話す内容をチェンジする
	if (transform_.scale_.x >= MAX_SIZE && pTalkImage_->IsLastDraw())
	{
		pTalkImage_->GetText()->ResetTotalDrawNum();
		pTalkImage_->NewCsvFile("Stage/World/World2/MobTalk_Movie2.csv");
	}
}