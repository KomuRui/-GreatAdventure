#include "BossEnemyMovie.h"
#include "../Manager/CoinManager/CoinManager.h"
#include "../Player/PlayerMovie.h"
#include "../Engine/ResourceManager/Fade.h"
#include "../Engine/ResourceManager/Audio.h"
#include "../Manager/GameManager/GameManager.h"
#include "../Engine/ResourceManager/CreateStage.h"
#include "../Scene/WorldScene/World2/WorldStage2.h"

//定数
namespace
{
	//最大サイズ
	static const float MAX_SIZE = 3.0f;
}


//コンストラクタ
BossEnemyMovie::BossEnemyMovie(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent,"Enemy/Model/MainBoss.fbx","BossEnemyMovie"), addScaleValue_(ZERO), hAudio_(-1), isChangeTalk_(false)
{}

//デストラクタ
BossEnemyMovie::~BossEnemyMovie()
{
	Audio::Stop(hAudio_);
}

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

	//音ロード
	hAudio_ = Audio::Load("Audio/BGM/World2/Movie1.wav");
	assert(hAudio_ >= ZERO);

	//音
	//Audio::PlayLoop(hAudio_);
}

//更新
void BossEnemyMovie::ChildUpdate()
{
	//Playerの方を向く
	LookObject(((PlayerMovie*)FindObject("Player"))->GetPosition(), vNormal_);

	//もし最後まで描画されていてかつ会話が変更されていてXボタンを押したのなら
	if (pTalkImage_->IsLastDraw() && isChangeTalk_ && Input::IsPadButtonDown(XINPUT_GAMEPAD_X))
	{
		//画像削除
		pTalkImage_->KillMe();

		//フェードイン
		Fade::SetFadeStatus(FADE_NORMAL_IN);
	}

	//ボスのステージかつフェードが最後まで終了していたらステージを削除してムービーのシーン作成
	if (Fade::isNormalFadeNotTransparency())
	{
		//削除
		GameManager::GetpStage()->GetCreateStage()->AllCreateStageDelete();

		//ボスステージ作成
		((WorldStage2*)GetParent())->CreateBossStage();

		//フェードアウト
		Fade::SetFadeStatus(FADE_NORMAL_OUT);
	}
}

//拡大する
void BossEnemyMovie::AddScale()
{
	//拡大
	ARGUMENT_INITIALIZE(transform_.scale_,Float3Add(transform_.scale_, { addScaleValue_,addScaleValue_,addScaleValue_ }));

	//もしコイン総数が0なら話す内容をチェンジする
	if (CoinManager::GetCoinNum() <= ZERO && pTalkImage_->IsLastDraw() && !isChangeTalk_)
	{
		ARGUMENT_INITIALIZE(isChangeTalk_, true);
		pTalkImage_->GetText()->ResetTotalDrawNum();
		pTalkImage_->NewCsvFile("Stage/World/World2/MobTalk_Movie2.csv");
	}
}