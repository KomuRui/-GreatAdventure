#include "TitleComplexModel.h"
#include "../Engine/Model.h"
#include "../Engine/Camera.h"

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

	//タイトル画面など表示するために先にファイルロードしておく
	pCreateStage = new CreateStage;
	pCreateStage->LoadFile(GetParent(), "TitleScene/StageInformation/TitleScene2.txt");
}

//更新の前に一回呼ばれる関数
void TitleComplexModel::StartUpdate()
{
}

//更新
void TitleComplexModel::Update()
{
	//y軸のポジションを徐々に下げていく
	transform_.position_.y -= SPEED;

	//yが-20より下に落ちたら
	if (transform_.position_.y < LIMIT_Y)
	{
		//カメラ振動
		Camera::SetCameraVibration(VIBRATION_INTENSITY);

		//タイトルなどを表示
		pCreateStage->LoadFileBasedCreateStage();

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
