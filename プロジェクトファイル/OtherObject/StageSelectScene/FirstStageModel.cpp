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
}

//コンストラクタ
FirstStageModel::FirstStageModel(GameObject* parent, std::string ModelPath, std::string name)
	:StageModelBase(parent,ModelPath, name)
{
}

//初期化
void FirstStageModel::ChildInitialize()
{
	//チェックポイントモデル追加
	((BaseSelectStage*)GetParent())->SetCheckPointModel(static_cast<int>(CheckPoint::FIRST),this);
}

//更新
void FirstStageModel::ChildUpdate()
{
	transform_.rotate_.y += ROTATION_ADD_VALUE;
}

//選択されている時にボタンを押された時
void FirstStageModel::SelectButtonPush()
{
	//フェードイン
	Fade::SetFadeStatus(FADE_CIRCLE_IN);

	//定数秒後に呼ぶ
	SetTimeMethod(3.0f);
}

//指定した時間で呼ばれるメソッド
void FirstStageModel::TimeMethod()
{
	//シーンチェンジ
	GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_TUTORIAL2);
}