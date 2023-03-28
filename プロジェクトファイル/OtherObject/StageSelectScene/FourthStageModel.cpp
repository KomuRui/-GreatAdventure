#include "FourthStageModel.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/CreateStage.h"
#include "../../Manager/GameManager/GameManager.h"
#include "BaseSelectStage.h"
#include "../../Engine/ResourceManager/Fade.h"

//定数
namespace
{
	static const XMFLOAT4 INITIALIZE_AMBIENT = { -0.6f, -0.6f, -0.6f, ZERO }; //初期アンビエント値
	static const float ROTATION_ADD_VALUE = 0.35f;	//回転する時の加算する値
	static const float CALL_TIMEMETHOD_TIME = 3.0f; //タイムメソッドを呼ぶ時間
}

//コンストラクタ
FourthStageModel::FourthStageModel(GameObject* parent, std::string ModelPath, std::string name)
	:StageModelBase(parent, ModelPath,name, "Image/StageSelect/FirstStage.png")
{
}

//初期化
void FourthStageModel::ChildInitialize()
{
	//チェックポイント追加
	((BaseSelectStage*)GetParent())->SetCheckPointModel(static_cast<int>(CheckPoint::FOURTH), this);

	//アンビエント設定
	Model::SetAmbient(hModel_, INITIALIZE_AMBIENT);
}

//更新
void FourthStageModel::ChildUpdate()
{
	transform_.rotate_.y += ROTATION_ADD_VALUE;
}

//選択されている時にボタンを押された時
void FourthStageModel::SelectButtonPush()
{
	//すでにフェードアウトしていたらこの先は処理しない
	if (Fade::GetFadeStatus() == FADE_CIRCLE_OUT)return;

	//フェードアウト
	Fade::SetFadeStatus(FADE_CIRCLE_OUT);

	//定数秒後に呼ぶ
	SetTimeMethod(CALL_TIMEMETHOD_TIME);
}

//指定した時間で呼ばれるメソッド
void FourthStageModel::TimeMethod()
{
	//シーンチェンジ
	GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_WORLD1);
}