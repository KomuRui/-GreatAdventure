#include "IconSelectUI.h"
#include "../../Engine/CreateStage.h"
#include "../../Engine/Easing.h"
#include "../../Engine/Text.h"
#include "../../Engine/Component/EasingMove.h"
#include "../../OtherObject/SelectPlanetController.h"
#include "../../Manager/ButtonManager/ButtonManager.h"

//定数
namespace
{
	static const XMFLOAT3 EASING_ONE_BEFORE_POS = { 2,0,0 }; //イージング1回目の移動前ポジション
	static const XMFLOAT3 EASING_ONE_AFTER_POS = { 0,0,0 };  //イージング1回目の移動前ポジション
	static const XMFLOAT3 EASING_TWO_BEFORE_POS = { 0,0,0 }; //イージング2回目の移動前ポジション
	static const XMFLOAT3 EASING_TWO_AFTER_POS = { -2,0,0 };  //イージング2回目の移動前ポジション

	static const float EASING_MOVE_TIME = 2.0f; //イージングの移動にかかる時間
}

//コンストラクタ
IconSelectUI::IconSelectUI(GameObject* parent)
	: GameObject(parent, "IconSelectUI"), isEasingChange_(false), iconModelPath_("")
{}

//初期化
void IconSelectUI::Initialize()
{

	////////////////////////////////イージングの初期設定////////////////////////////////////

	ARGUMENT_INITIALIZE(pEasingMove_, new EasingMove(&transform_.position_, EASING_ONE_BEFORE_POS, EASING_ONE_AFTER_POS, EASING_MOVE_TIME, Easing::OutQuart))

	////////////////////////////////transform////////////////////////////////////

	ARGUMENT_INITIALIZE(transform_.position_, EASING_ONE_BEFORE_POS);

	/////////////////ファイル読み込んでステージの各オブジェクト設置///////////////////

	pCreateStage_ = new CreateStage;
	pCreateStage_->LoadFileCreateStage(this, "Stage/UserSelect/StageInformation/IconSelectUI.txt");
}

//更新の前に一度だけ呼ばれる
void IconSelectUI::StartUpdate()
{
}

//更新
void IconSelectUI::Update()
{
	//イージングの動きが最後まで終わっているかつイージングの情報を一回でも変更していたら
	if (pEasingMove_->Move() && isEasingChange_)
	{
		//モデルパスを設定
		SelectPlanetController::SetIconModelPath(iconModelPath_);

		//削除
		KillMe();
	}
}

//描画
void IconSelectUI::Draw()
{

}

//解放
void IconSelectUI::Release()
{
}

//イージングの動き方変更
void IconSelectUI::ChangeEasingMove(std::string path)
{
	//変更されている場合はこの先の処理をしない
	if (isEasingChange_) return;

	//アイコンのモデルパス保存
	ARGUMENT_INITIALIZE(iconModelPath_, path);

	//変更したに変更
	ARGUMENT_INITIALIZE(isEasingChange_, true);

	//情報変更
	pEasingMove_->Reset(&transform_.position_, EASING_TWO_BEFORE_POS, EASING_TWO_AFTER_POS, EASING_MOVE_TIME, Easing::InQuart);
}