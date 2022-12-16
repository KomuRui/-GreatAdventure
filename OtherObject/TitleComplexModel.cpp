#include "TitleComplexModel.h"
#include "../Engine/Model.h"
#include "../Engine/Camera.h"
#include "../Engine/CreateStage.h"

//コンストラクタ
TitleComplexModel::TitleComplexModel(GameObject* parent)
	:GameObject(parent, "TitleComplexModel"), hModel_(-1)
{
}

//初期化
void TitleComplexModel::Initialize()
{
	//モデルデータロード
	hModel_ = Model::Load("TitleScene/Model/TitleComplexModel.fbx");
	assert(hModel_ >= ZERO);

}

//更新の前に一回呼ばれる関数
void TitleComplexModel::StartUpdate()
{
}

//更新
void TitleComplexModel::Update()
{
	//y軸のポジションを徐々に下げていく
	transform_.position_.y -= 0.1;

	//yが-20より下に落ちたら
	if (transform_.position_.y < -20.0f)
	{
		//カメラ振動
		Camera::SetCameraVibration(0.4f);

		//タイトル画面など配置
		CreateStage* pCreateStage = new CreateStage;
		pCreateStage->LoadFile(GetParent(), "TitleScene/StageInformation/TitleScene2.txt");

		//自身を削除
		KillMe();
	}
}

//描画
void TitleComplexModel::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//解放
void TitleComplexModel::Release()
{
}
