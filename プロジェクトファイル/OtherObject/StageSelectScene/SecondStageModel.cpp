#include "SecondStageModel.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/CreateStage.h"
#include "../../Manager/GameManager/GameManager.h"
#include "BaseSelectStage.h"
#include "../../Engine/ResourceManager/Fade.h"
//定数
namespace
{
	static const XMFLOAT3 ROTATION_MODEL_POSITION = { -39.5f, ZERO, 1.2f }; //回転モデルのポジション
	static const float ROTATION_ADD_VALUE = 0.30f;	//回転する時の加算する値
	static const float CALL_TIMEMETHOD_TIME = 3.0f; //タイムメソッドを呼ぶ時間
}

//コンストラクタ
SecondStageModel::SecondStageModel(GameObject* parent, std::string ModelPath, std::string name)
	:StageModelBase(parent,ModelPath,name, "Image/StageSelect/SecondStage.png"), hRotationModel_(-1)
{
}

//初期化
void SecondStageModel::ChildInitialize()
{
	///////////////チェックポイントモデル追加///////////////////

	((BaseSelectStage*)GetParent())->SetCheckPointModel(static_cast<int>(CheckPoint::SECOND), this);

	///////////////firstStageは常に解放状態に///////////////////

	ARGUMENT_INITIALIZE(isStageRelease_, true);

	///////////////モデルデータのロード///////////////////

	hRotationModel_ = Model::Load("Stage/StageSelect/second/secondStageModel2.fbx");
	assert(hRotationModel_ >= ZERO);

	/////////////////明るさ設定/////////////////

	Model::SetBrightness(hRotationModel_, 1.0f);

	//////////////////トランスフォーム初期化/////////////////////

	ARGUMENT_INITIALIZE(tRotation_.position_, ROTATION_MODEL_POSITION);
	ARGUMENT_INITIALIZE(tRotation_.pParent_, transform_.pParent_);
}

//更新
void SecondStageModel::ChildUpdate()
{
	//回転
	tRotation_.rotate_.y += ROTATION_ADD_VALUE;
}

//描画
void SecondStageModel::ChildDraw()
{
	Model::SetTransform(hRotationModel_, tRotation_);
	Model::Draw(hRotationModel_);
}

//選択されている時にボタンを押された時
void SecondStageModel::SelectButtonPush()
{
	//すでにフェードアウトしていたらこの先は処理しない
	if (Fade::GetFadeStatus() == FADE_CIRCLE_OUT)return;

	//フェードアウト
	Fade::SetFadeStatus(FADE_CIRCLE_OUT);

	//定数秒後に呼ぶ
	SetTimeMethod(CALL_TIMEMETHOD_TIME);
}

//指定した時間で呼ばれるメソッド
void SecondStageModel::TimeMethod()
{
	//シーンチェンジ
	GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_WORLD1);
}