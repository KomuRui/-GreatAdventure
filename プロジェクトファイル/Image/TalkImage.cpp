#include "TalkImage.h"
#include "../Engine/Image.h"
#include "../Engine/Input.h"
#include "../Engine/ImGuiSet.h"

//定数
namespace
{

	//文字
	static const float TEXT_SCALE = 0.3f;

	//描画スピード
	static const float NORMAL_DRAW_SPEED = 0.1f; //普通
	static const float FAST_DRAW_SPEED = 0.05f;  //速い

	//文字列

	static const int TEXT_MAX = 6;

	static const wchar_t *TEXT[TEXT_MAX] = {
		{ L"こんにちは!,SUPER-STAR-GALAXY,のセカイへようこそ!"},
		{ L"わたしのなまえはMr.Dです!,あなたのサポ-トをしたり,たんけんのテダスケをするぞ!"},
		{ L"さてあなたのオヒメサマが,ボスにとらわれてしまいました...,いろいろなほしをたんけんして,たすけにいきましょう!"},
		{ L"もしオヒメサマをたすけることができたら,オヒメサマとキスできるかも..."},
		{ L"たんけんのとちゅうに,コインをたくさんあつめておくと,あとでいいことがおきるかも!!!"},
		{ L"チュ-トリアルでライフがつきたら,またこのステ-ジからはじまるぞ!"},
	};
}

//コンストラクタ
TalkImage::TalkImage(GameObject* parent)
	: GameObject(parent, "TalkImage"), hBasePict_(-1),hCharaPict_(-1), hNextPict_(-1),pText_(new Text), drawTextNum_(ZERO),
	isLastDraw_(false)
{
}

//初期化
void TalkImage::Initialize()
{
	///////////////文字のロード///////////////////

	//初期化
	pText_->Initialize(NORMAL_DRAW_SPEED);

	//ファイルロード
	ARGUMENT_INITIALIZE(pCsv_, new CsvReader("Stage/Tutorial/MobTalk1.xlsx"));

	///////////////画像データのロード///////////////////

	hBasePict_ = Image::Load("Image/Text/Talk.png");
	assert(hBasePict_ >= ZERO);

	hCharaPict_ = Image::Load("Image/MainMob/MainMobImage.png");
	assert(hCharaPict_ >= ZERO);

	hNextPict_ = Image::Load("Image/Text/Next.png");
	assert(hNextPict_ >= ZERO);

	/////////////////////////各Transform/////////////////////////

	//ベース
	ARGUMENT_INITIALIZE(tBase_.position_.x, GetPrivateProfilefloat("POSITION", "BaseX", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tBase_.position_.y, GetPrivateProfilefloat("POSITION", "BaseY", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tBase_.position_.z,1.0f);

	ARGUMENT_INITIALIZE(tBase_.scale_.x, GetPrivateProfilefloat("SCALE", "BaseX", "2.8", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tBase_.scale_.y, GetPrivateProfilefloat("SCALE", "BaseY", "0.8", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tBase_.scale_.z, 1.0f);

	//キャラ
	ARGUMENT_INITIALIZE(tChara_.position_.x, GetPrivateProfilefloat("POSITION", "CharaX", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tChara_.position_.y, GetPrivateProfilefloat("POSITION", "CharaY", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tChara_.position_.z, 1.0f);

	ARGUMENT_INITIALIZE(tChara_.scale_.x, GetPrivateProfilefloat("SCALE", "CharaX", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tChara_.scale_.y, GetPrivateProfilefloat("SCALE", "CharaY", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tChara_.scale_.z, 1.0f);

	//Next
	ARGUMENT_INITIALIZE(tNext_.position_.x, GetPrivateProfilefloat("POSITION", "NextX", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tNext_.position_.y, GetPrivateProfilefloat("POSITION", "NextY", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tNext_.position_.z, 1.0f);

	ARGUMENT_INITIALIZE(tNext_.scale_.x, GetPrivateProfilefloat("SCALE", "NextX", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tNext_.scale_.y, GetPrivateProfilefloat("SCALE", "NextY", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tNext_.scale_.z, 1.0f);
}

//更新の前に一度だけ呼ばれる
void TalkImage::StartUpdate()
{
}

//更新
void TalkImage::Update()
{
	//Bが押されているのなら
	if (Input::IsPadButton(XINPUT_GAMEPAD_X))
		pText_->SetDrawSpeed(FAST_DRAW_SPEED);
	else
		pText_->SetDrawSpeed(NORMAL_DRAW_SPEED);
}

//描画
void TalkImage::Draw()
{
	//画像描画
	Image::SetTransform(hBasePict_, tBase_);
	Image::Draw(hBasePict_);

	Image::SetTransform(hCharaPict_, tChara_);
	Image::Draw(hCharaPict_);

	//文字描画()もし文字が最後まで描画していたら
	if (pText_->SlowlyDraw(1050, 800, TEXT[drawTextNum_], TEXT_SCALE))
	{
		//Next画像を表示
		Image::SetTransform(hNextPict_, tNext_);
		Image::Draw(hNextPict_);

		//最後の文字列を描画し終わっているのなら
		if (drawTextNum_ >= TEXT_MAX - 1)
			ARGUMENT_INITIALIZE(isLastDraw_, true);

		//もしBボタンを押したなら
		if (Input::IsPadButtonDown(XINPUT_GAMEPAD_X))
		{
			//描画する文字列変更
			drawTextNum_++;

			//描画できる文字総数を初期化
			pText_->SetTotalDrawNum(ZERO);

			//最大文字列以上かつループするなら初期化
			if (drawTextNum_ >= TEXT_MAX)
				ARGUMENT_INITIALIZE(drawTextNum_, ZERO);

		}
	}
}

//解放
void TalkImage::Release()
{
}
