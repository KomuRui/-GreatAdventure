#include "MiniGameStage.h"
#include "../../Engine/Model.h"
#include "../../Engine/Light.h"
#include "../../Engine/Camera.h"
#include "../../Gimmick/Warp.h"
#include "../../Engine/CreateStage.h"

//コンストラクタ
MiniGameStage::MiniGameStage(GameObject* parent)
	:Stage(parent, "MiniGameStage")
{
	//画角
	ARGUMENT_INITIALIZE(fieldAngle_, 45);

	//ライトの強さ
	ARGUMENT_INITIALIZE(lightIntensity_,4);
}

//初期化
void MiniGameStage::Initialize()
{
	/////////////////////モデルデータのロード///////////////////////

	hModel_[Base] = Model::Load("Stage/MiniGame/StraightStage.fbx");
	hModel_[PolyModel] = Model::Load("Stage/MiniGame/StraightStage.fbx");

	///////////////////////////各種設定/////////////////////////////

	//レイの判定にBaseをいれたいのでtrueにしておく
	Model::SetRayFlag(hModel_[Base], true);

	//明るさを設定
	Model::SetBrightness(hModel_[Base], 1.0f);

	//PolyModelを透明に設定(軸を確認するためだけに使うため)
	Model::SetAlpha(hModel_[PolyModel], ZERO);

	//画角
	Camera::SetFieldAngle(fieldAngle_);

	//カメラの上ベクトル
	Camera::SetUpDirection(UP_VECTOR);

	//ライトの強さ
	Light::SetPlayerIntensity(lightIntensity_);

	//Playerの初期位置
	ARGUMENT_INITIALIZE(pos_,XMFLOAT3(ZERO,ZERO,ZERO));

	//3Dなのでtrueにする
	ARGUMENT_INITIALIZE(threeDflag_,true);

	//球体使用しているのでtrue
	ARGUMENT_INITIALIZE(circleFlag_,true);

}

//更新
void MiniGameStage::Update()
{
}

//描画
void MiniGameStage::Draw()
{
	Model::SetTransform(hModel_[Base], transform_);
	Model::Draw(hModel_[Base]);
}

//解放
void MiniGameStage::Release()
{
}
