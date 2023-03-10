#include "Princess.h"
#include "../Manager/CoinManager/CoinManager.h"
#include "../Player/PlayerMovie.h"
#include "../Engine/ResourceManager/Fade.h"
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
Princess::Princess(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent, "Enemy/Model/MainBoss.fbx", "Princess")
{}

//初期化
void Princess::ChildInitialize()
{
	//話している時の画像・テキスト表示
	ARGUMENT_INITIALIZE(pTalkImage_, Instantiate<TalkImage>(GetParent()->GetParent()->GetParent()));
}

//更新
void Princess::ChildUpdate()
{
	//Playerの方を向く
	LookObject(((PlayerMovie*)FindObject("Player"))->GetPosition(), vNormal_);

	//もし最後まで描画されていてかつ最大サイズでXボタンを押したのなら
	if (pTalkImage_->IsLastDraw() && transform_.scale_.x >= MAX_SIZE && Input::IsPadButtonDown(XINPUT_GAMEPAD_X))
	{
		//画像削除
		pTalkImage_->KillMe();

		//フェードイン
		Fade::SetFadeStatus(FADE_NORMAL_IN);
	}

	//ボスのステージかつフェードが最後まで終了していたらステージを削除してムービーのシーン作成
	if (Fade::isNormalFadeNotTransparency())
	{
		//フェードアウト
		Fade::SetFadeStatus(FADE_NORMAL_OUT);
	}
}

