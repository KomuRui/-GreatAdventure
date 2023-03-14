#include "FirstStageModel.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/CreateStage.h"
#include "../../Manager/GameManager/GameManager.h"
#include "BaseSelectStage.h"
#include "../../Engine/ResourceManager/Fade.h"

//定数
namespace
{
	static const float ROTATION_ADD_VALUE = 0.25f;	//回転する時の加算する値
	static const float CALL_TIMEMETHOD_TIME = 3.0f; //タイムメソッドを呼ぶ時間
}

//コンストラクタ
FirstStageModel::FirstStageModel(GameObject* parent, std::string ModelPath, std::string name)
	:StageModelBase(parent,ModelPath, name,"Image/StageSelect/FirstStage.png")
{
}

//初期化
void FirstStageModel::ChildInitialize()
{
	//チェックポイントモデル追加
	((BaseSelectStage*)GetParent())->SetCheckPointModel(static_cast<int>(CheckPoint::FIRST),this);

	//最初はfirstStageが選択されているように
	ARGUMENT_INITIALIZE(isSelect_, true);

	//firstStageは常に解放状態に
	ARGUMENT_INITIALIZE(isStageRelease_, true);
}

//更新
void FirstStageModel::ChildUpdate()
{
	transform_.rotate_.y += ROTATION_ADD_VALUE;
}

//選択されている時にボタンを押された時
void FirstStageModel::SelectButtonPush()
{
	//すでにフェードアウトしていたらこの先は処理しない
	if (Fade::GetFadeStatus() == FADE_CIRCLE_OUT)return;

	//フェードアウト
	Fade::SetFadeStatus(FADE_CIRCLE_OUT);

	//定数秒後に呼ぶ
	SetTimeMethod(CALL_TIMEMETHOD_TIME);
}

//指定した時間で呼ばれるメソッド
void FirstStageModel::TimeMethod()
{
	//シーンチェンジ
	GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_TUTORIAL2);
}