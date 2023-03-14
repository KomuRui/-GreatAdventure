#include "ThirdStageModel.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/CreateStage.h"
#include "../../Manager/GameManager/GameManager.h"
#include "BaseSelectStage.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../OtherObject/UserInfomation.h"

//定数
namespace
{
	static const XMFLOAT4 INITIALIZE_AMBIENT = { -0.7, -0.7, -0.7, ZERO }; //初期アンビエント値
	static const float ROTATION_ADD_VALUE = 0.25f;	//回転する時の加算する値
	static const float CALL_TIMEMETHOD_TIME = 3.0f; //タイムメソッドを呼ぶ時間
}

//コンストラクタ
ThirdStageModel::ThirdStageModel(GameObject* parent, std::string ModelPath, std::string name)
	:StageModelBase(parent,ModelPath,name, "Image/StageSelect/ThirdStage.png")
{
}

//初期化
void ThirdStageModel::ChildInitialize()
{
	//チェックポイント追加
	((BaseSelectStage*)GetParent())->SetCheckPointModel(static_cast<int>(CheckPoint::THIRD), this);

	//もし解放ステージが3より小さいなら解放しない
	if(UserInfomation::GetStageReleaseNum() < 3)
		Model::SetAmbient(hModel_, INITIALIZE_AMBIENT);
	//3以上なら解放
	else
	ARGUMENT_INITIALIZE(isStageRelease_, true);
}

//更新
void ThirdStageModel::ChildUpdate()
{
	transform_.rotate_.y += ROTATION_ADD_VALUE;
}

//選択されている時にボタンを押された時
void ThirdStageModel::SelectButtonPush()
{
	//すでにフェードアウトしていたらこの先は処理しない
	if (Fade::GetFadeStatus() == FADE_CIRCLE_OUT)return;

	//フェードアウト
	Fade::SetFadeStatus(FADE_CIRCLE_OUT);

	//定数秒後に呼ぶ
	SetTimeMethod(CALL_TIMEMETHOD_TIME);
}

//指定した時間で呼ばれるメソッド
void ThirdStageModel::TimeMethod()
{
	//シーンチェンジ
	GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_WORLD2);
}