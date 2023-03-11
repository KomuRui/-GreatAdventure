#include "NewFileUI.h"
#include "../../Engine/ResourceManager/CreateStage.h"
#include "../../Engine/ResourceManager/Easing.h"
#include "../../Engine/ResourceManager/Text.h"
#include "../../Engine/Component/EasingMove.h"
#include "../../Manager/ButtonManager/ButtonManager.h"
#include "IconSelectUI.h"

//定数
namespace
{
	static const XMFLOAT3 EASING_ONE_BEFORE_POS = { 2,0,0 }; //イージング1回目の移動前ポジション
	static const XMFLOAT3 EASING_ONE_AFTER_POS =  { 0,0,0 }; //イージング1回目の移動後ポジション
	static const XMFLOAT3 EASING_TWO_BEFORE_POS = { 0,0,0 }; //イージング2回目の移動前ポジション
	static const XMFLOAT3 EASING_TWO_AFTER_POS = { -2,0,0 }; //イージング2回目の移動後ポジション

	static const float EASING_MOVE_TIME = 2.0f; //イージングの移動にかかる時間
}

//コンストラクタ
NewFileUI::NewFileUI(GameObject* parent)
	: GameObject(parent, "NewFileUI"), isEasingChange_(false)
{}

//初期化
void NewFileUI::Initialize()
{
	////////////////////////////////イージングの初期設定////////////////////////////////////

	ARGUMENT_INITIALIZE(pEasingMove_, new EasingMove(&transform_.position_, EASING_ONE_BEFORE_POS, EASING_ONE_AFTER_POS, EASING_MOVE_TIME, Easing::OutQuart))

	////////////////////////////////transform////////////////////////////////////

	ARGUMENT_INITIALIZE(transform_.position_, EASING_ONE_BEFORE_POS);

	/////////////////ファイル読み込んでステージの各オブジェクト設置///////////////////

	pCreateStage_ = new CreateStage;
	pCreateStage_->LoadFileCreateStage(this, "Stage/UserSelect/StageInformation/NewFileUI.txt");
}

//更新の前に一度だけ呼ばれる
void NewFileUI::StartUpdate()
{
}

//更新
void NewFileUI::Update()
{
	//イージングの動きが最後まで終わっているかつイージングの情報を一回でも変更していたら
	if (pEasingMove_->Move() && isEasingChange_)
	{
		//リセットする
		ButtonManager::Reset();

		//アイコン選択UI作成
		Instantiate<IconSelectUI>(GetParent());

		//削除
		KillMe();
	}
}

//描画
void NewFileUI::Draw()
{

}

//解放
void NewFileUI::Release()
{
}

//イージングの動き方変更
void NewFileUI::ChangeEasingMove()
{
	//変更されている場合はこの先の処理をしない
	if (isEasingChange_) return;

	//変更したに変更
	ARGUMENT_INITIALIZE(isEasingChange_, true);

	//情報変更
	pEasingMove_->Reset(&transform_.position_, EASING_TWO_BEFORE_POS, EASING_TWO_AFTER_POS, EASING_MOVE_TIME, Easing::InQuart);
}