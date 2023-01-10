#include "TalkMainMob.h"
#include "../Engine/ImGuiSet.h"

//定数
namespace
{
	////////////////////////////アニメーション////////////////////////////

	static const int START_FRAME = 0;	  //開始フレーム
	static const int END_FRAME = 120;     //終了フレーム
	static const float ANIM_SPEED = 1.0f; //アニメーションの再生速度

	////////////////////////////その他////////////////////////////

	static const float PLAYER_LOOK_DISTANCE = 8; //Playerの方を向く時の距離
}

//コンストラクタ
TalkMainMob::TalkMainMob(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent, modelPath, name), isTalk_(false), toPlayer_(XMMatrixIdentity()), isLookPlayer_(false), hPict_(-1),
	pTalkImage_(nullptr)
{}

//更新の前に一度だけ呼ばれる
void TalkMainMob::ChildStartUpdate()
{
	///////////////画像データのロード///////////////////

	hPict_ = Image::Load("Image/Text/Speak.png");
	assert(hPict_ >= ZERO);

	////////////画像のトランスフォーム設定///////////////

	ARGUMENT_INITIALIZE(tPict_.position_.x, GetPrivateProfilefloat("POSITION", "TalkX", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tPict_.position_.y, GetPrivateProfilefloat("POSITION", "TalkY", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tPict_.position_.z, 1.0f);

	ARGUMENT_INITIALIZE(tPict_.scale_.x, GetPrivateProfilefloat("SCALE", "TalkX", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tPict_.scale_.y, GetPrivateProfilefloat("SCALE", "TalkY", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tPict_.scale_.z, 1.0f);
}

//更新
void TalkMainMob::ChildUpdate()
{
	//Playerの方を向く
	LookPlayer();

	//もし話している状態なら
	if (isTalk_)
	{
		//文字が最後まで描画されていてかつBボタンを押したのなら
		if (pTalkImage_->IsLastDraw() && Input::IsPadButtonDown(XINPUT_GAMEPAD_X))
		{
			//カメラ
			GameManager::GetpPlayer()->SetCamLong();

			//Player動くように
			GameManager::GetpPlayer()->SetAnimFlag(true);
			GameManager::GetpPlayer()->Enter();

			//画像削除
			pTalkImage_->KillMe();

			//話していない状態に
			ARGUMENT_INITIALIZE(isTalk_, false);
		}
		else
		{
			//カメラ
			GameManager::GetpPlayer()->SetCamShort();

			//Playerをこのオブジェクトの方向くようにする
			GameManager::GetpPlayer()->LookObject(transform_.position_, GameManager::GetpPlayer()->GetUp());

			//Player動かないようにする
			GameManager::GetpPlayer()->SetAnimFlag(false);
			GameManager::GetpPlayer()->Leave();
		}
	}
}

//描画
void TalkMainMob::ChildDraw()
{
	//Playerとの距離が指定距離以内かつ話していない状態なら画像表示
	if (IsInSpecifiedDistance() && !isTalk_)
	{
		Image::SetTransform(hPict_, tPict_);
		Image::Draw(hPict_);
	}
}

//Playerの方を向く
void TalkMainMob::LookPlayer()
{
	//もし一回でもPlayerの方向いていたら
	if (isLookPlayer_)
		transform_.mmRotate_ = XMMatrixInverse(nullptr, toPlayer_);

	//Playerとの距離が指定距離以内ならPlayerの方を向く
	if (IsInSpecifiedDistance())
	{
		//もし話していない状態でBボタンを押したのなら
		if (!isTalk_ && Input::IsPadButtonDown(XINPUT_GAMEPAD_X))
		{
			//話している時の画像・テキスト表示
			ARGUMENT_INITIALIZE(pTalkImage_,Instantiate<TalkImage>(GetParent()->GetParent()->GetParent()));

			//話している状態に
			ARGUMENT_INITIALIZE(isTalk_, true);
		}

		//Playerの方を向く
		toPlayer_ = XMMatrixLookAtLH(XMVectorSet(ZERO, ZERO, ZERO, ZERO), XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&transform_.position_), up_);
		transform_.mmRotate_ = XMMatrixInverse(nullptr, toPlayer_);

		//向いたらtrueにする
		ARGUMENT_INITIALIZE(isLookPlayer_, true);
	}
}

//指定距離内に入っているかどうか
bool TalkMainMob::IsInSpecifiedDistance()
{
	return (RangeCalculation(transform_.position_, GameManager::GetpPlayer()->GetPosition()) < PLAYER_LOOK_DISTANCE);
}