#include "NewFileCancelButton.h"
#include "../../../Engine/ResourceManager/Global.h"
#include "../../../Engine/ResourceManager/Image.h"
#include "../../../Engine/ResourceManager/Time.h"
#include "../../../Engine/ResourceManager/Easing.h"
#include "../../../OtherObject/SelectPlanetController.h"
#include "../../../Manager/ButtonManager/ButtonManager.h"
#include "../NewFileUI.h"

//コンストラクタ
NewFileCancelButton::NewFileCancelButton(GameObject* parent, std::string modelPath, std::string name)
	:ButtonBase(parent, modelPath,name), hNotSelectPict_(-1), hSelectPict_(-1)
{}

//初期化
void NewFileCancelButton::ChildInitialize()
{
	//押すの許可しない
	ARGUMENT_INITIALIZE(isPushOk_, false);

	//セレクト画像の番号取得
	ARGUMENT_INITIALIZE(hNotSelectPict_, hPict_);

	//ロード
	ARGUMENT_INITIALIZE(hSelectPict_, Image::Load("Image/UserSelect/Cancel_Select.png"));
}

//更新
void NewFileCancelButton::ChildButtonUpdate()
{
	//ボタン押すの許可するか取得
	ARGUMENT_INITIALIZE(isPushOk_, ((NewFileUI*)GetParent())->IsButtonPushOk());
}

//ボタンが押されたら何するか
void NewFileCancelButton::IsButtonPush()
{
	//選択中に戻る状態にセット
	SelectPlanetController::SetStatus(SelectPlanetStatus::BackSelecting);
	SelectPlanetController::ResetPlanetMove();

	//リセットする
	ButtonManager::Reset();

	//選択状態解除
	ARGUMENT_INITIALIZE(isSelect_, false);

	//元へ戻ると親に伝える
	((NewFileUI*)GetParent())->ChangeEasingMoveReturn();
}

//ボタンが選択された瞬間に何をするか
void NewFileCancelButton::IsButtonSelect(){ ARGUMENT_INITIALIZE(hPict_, hSelectPict_);}

//ボタンが選択解除された瞬間に何をするか
void NewFileCancelButton::IsButtonSelectRelease(){ ARGUMENT_INITIALIZE(hPict_, hNotSelectPict_);}