#include "BossWarningImage.h"
#include "../../../Engine/ResourceManager/Image.h"
#include "../../../Engine/Component/EasingMove.h"
#include "../../../Engine/ResourceManager/Easing.h"
#include "../../../Engine/ResourceManager/Time.h"
#include "../../../Enemy/BossEnemy.h"

//定数
namespace
{
	static const XMFLOAT3 EASING_ONE_BEFORE_POS = { 3,0,0 }; //イージング1回目の移動前ポジション
	static const XMFLOAT3 EASING_ONE_AFTER_POS = { 0,0,0 }; //イージング1回目の移動後ポジション
	static const XMFLOAT3 EASING_TWO_BEFORE_POS = { 0,0,0 }; //イージング2回目の移動前ポジション
	static const XMFLOAT3 EASING_TWO_AFTER_POS = { -3,0,0 }; //イージング2回目の移動後ポジション
	 
	static const float ALPHA_ADD_VALUE = 0.05f;    //アルファ値計算するときに加算する値
	static const float NEXT_EASING_CHANGE = 3.0f;  //アルファ値計算するときに加算する値
	static const float EASING_MOVE_TIME = 2.0f;	   //イージングの移動にかかる時間
}

//コンストラクタ
BossWarningImage::BossWarningImage(GameObject* parent)
	: GameObject(parent), hWarningPict_(-1), hBackGround_(-1),isEasingChange_(false), isFinish_(false), 
	backGroundAlpha_(ZERO), sign_(1), hTime_(ZERO)
{
}

//初期化
void BossWarningImage::Initialize()
{
	///////////////画像データのロード///////////////////

	hWarningPict_ = Image::Load("Image/World2/BossWarning.png");
	assert(hWarningPict_ >= ZERO);

	hBackGround_ = Image::Load("Image/World2/Background.png");
	assert(hBackGround_ >= ZERO);

	///////////////タイマー追加///////////////////

	ARGUMENT_INITIALIZE(hTime_, Time::Add());
	Time::Lock(hTime_);

	////////////////////////////////イージングの初期設定////////////////////////////////////

	ARGUMENT_INITIALIZE(pEasingMove_, new EasingMove(&transform_.position_, EASING_ONE_BEFORE_POS, EASING_ONE_AFTER_POS, EASING_MOVE_TIME, Easing::OutQuart))

}

//更新
void BossWarningImage::Update()
{
	//イージングの動きが最後まで終了したか
	bool isEasingFinish = pEasingMove_->Move();

	//イージングの動きが最後まで終わっているかつイージングの情報を変更していないのなら
	if (isEasingFinish && !isEasingChange_)
	{
		//タイムがロックされているのならタイマースタート
		if(Time::isLock(hTime_))Time::UnLock(hTime_);
	}

	//イージングの動きが最後まで終わっているかつイージングの情報を変更しているのなら終了したに変更
	if (isEasingFinish && isEasingChange_ && !isFinish_)
	{
		//ボスの話す画像描画するように
		((BossEnemy*)FindObject("BossEnemy"))->SetTalkImageDraw();

		//終了に変更
		ARGUMENT_INITIALIZE(isFinish_, true);
	}

	//もしタイマーが定数秒以上経過していてイージングの情報を変更していないなら
	if (Time::GetTimef(hTime_) >= NEXT_EASING_CHANGE && !isEasingChange_)
	{
		//変更したに変更
		ARGUMENT_INITIALIZE(isEasingChange_, true);

		//イージングの動き方変更
		pEasingMove_->Reset(&transform_.position_, EASING_TWO_BEFORE_POS, EASING_TWO_AFTER_POS, EASING_MOVE_TIME, Easing::InQuart);
	}
}

//描画
void BossWarningImage::Draw()
{
	//終了していたらこの先処理しない
	if (isFinish_) return;

	//タイマーのロックが解除されていたら
	if (!Time::isLock(hTime_))
	{
		//背景透明度の計算
		BackGroundAlphaCalc();

		//表示用transform
		Transform t;

		//背景描画
		Image::SetTransform(hBackGround_, t);
		Image::SetAlpha(hBackGround_, backGroundAlpha_);
		Image::Draw(hBackGround_);
	}

	//警告
	Image::SetTransform(hWarningPict_, transform_);
	Image::Draw(hWarningPict_);
}

//背景透明度の計算
void BossWarningImage::BackGroundAlphaCalc()
{
	//透明度計算
	backGroundAlpha_ += ALPHA_ADD_VALUE * sign_;

	//範囲外の時の計算
	if (backGroundAlpha_ > 1)
	{
		sign_ *= -1;
		ARGUMENT_INITIALIZE(backGroundAlpha_, 1);
	}
	if (backGroundAlpha_ < ZERO)
	{
		sign_ *= -1;
		ARGUMENT_INITIALIZE(backGroundAlpha_, ZERO);
	}
}