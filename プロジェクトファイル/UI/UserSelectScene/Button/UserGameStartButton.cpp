#include "UserGameStartButton.h"
#include "../../../Engine/ResourceManager/Global.h"
#include "../../../Engine/ResourceManager/Image.h"
#include "../../../Engine/ResourceManager/Time.h"
#include "../../../Engine/ResourceManager/Easing.h"
#include "../../../Engine/Component/EasingMove.h"
#include "../../../OtherObject/UserInfomation.h"
#include "../../../Manager/GameManager/GameManager.h"
#include "../../../Manager/CoinManager/CoinManager.h"
#include "../NewFileUI.h"

//定数
namespace
{
	static const float EASING_MOVE_TIME = 2.0f; //イージングの移動にかかる時間
}

//コンストラクタ
UserGameStartButton::UserGameStartButton(GameObject* parent, std::string modelPath, std::string name)
	:ButtonBase(parent, modelPath, name), hNotSelectPict_(-1), hSelectPict_(-1)
{}

//初期化
void UserGameStartButton::ChildInitialize()
{
	////////////////////////////////イージングの初期設定////////////////////////////////////

	ARGUMENT_INITIALIZE(easingAfterPos_, XMFLOAT3(0.5, -0.5, ZERO));
	ARGUMENT_INITIALIZE(easingBeforePos_,XMFLOAT3(easingAfterPos_.x, easingAfterPos_.y - 1.0f, easingAfterPos_.z));
	ARGUMENT_INITIALIZE(pEasingMove_, new EasingMove(&transform_.position_, easingBeforePos_, easingAfterPos_, EASING_MOVE_TIME, Easing::OutQuart))

	////////////////////////////////画像の初期設定////////////////////////////////////

	ARGUMENT_INITIALIZE(hNotSelectPict_, hPict_);
	ARGUMENT_INITIALIZE(hSelectPict_, Image::Load("Image/UserSelect/Ok_Select.png"));
}

//更新
void UserGameStartButton::ChildButtonUpdate()
{
	//移動
	pEasingMove_->Move();
}

//ボタンが押されたら何するか
void UserGameStartButton::IsButtonPush()
{
	//解放ステージの数を取得
	int num = UserInfomation::GetStageReleaseNum();

	//もし1ならチュートリアルシーンからスタート
	if (num == 1)
		GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_TUTORIAL1);
	//それ以外ならHomeSceneからスタート
	else
		GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_HOME);

	//コインの総数をセット
	CoinManager::SetCoinNum(UserInfomation::GetCoinNum());

}

//ボタンが選択された瞬間に何をするか
void UserGameStartButton::IsButtonSelect() { ARGUMENT_INITIALIZE(hPict_, hSelectPict_); }

//ボタンが選択解除された瞬間に何をするか
void UserGameStartButton::IsButtonSelectRelease() { ARGUMENT_INITIALIZE(hPict_, hNotSelectPict_); }

//イージングリセット
void UserGameStartButton::ResetEasing() { pEasingMove_->Reset(&transform_.position_, easingAfterPos_, easingBeforePos_, EASING_MOVE_TIME, Easing::OutQuart);}