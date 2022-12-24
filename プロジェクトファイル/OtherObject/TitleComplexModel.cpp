#include "TitleComplexModel.h"
#include "../Engine/Model.h"
#include "../Engine/Camera.h"

//定数
namespace
{
	static const float SPEED = 0.1f;               //スピード
	static const float VIBRATION_INTENSITY = 0.2f; //振動の強さ
	static const float LIMIT_Y = -20.0f;           //y軸のポジション限界値
	static const float ATTENUATION = 0.003f;       //減衰値
}

//コンストラクタ
TitleComplexModel::TitleComplexModel(GameObject* parent)
	:GameObject(parent, "TitleComplexModel"), hModel_(-1)
{
}

//初期化
void TitleComplexModel::Initialize()
{
	//モデルデータロード
	hModel_ = Model::Load("Stage/Title/Model/TitleComplexModel.fbx");
	assert(hModel_ >= ZERO);

	//タイトル画面など表示するために先にファイルロードしておく
	pCreateStage = new CreateStage;
	pCreateStage->LoadFile(GetParent(), "Stage/Title/StageInformation/TitleScene2.txt");
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
		Camera::SetCameraVibration(VIBRATION_INTENSITY, ATTENUATION);

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
