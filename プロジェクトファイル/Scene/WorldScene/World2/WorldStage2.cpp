#include "WorldStage2.h"
#include "../../../Engine/ResourceManager/Model.h"
#include "../../../Engine/GameObject/Light.h"
#include "../../../Engine/GameObject/Camera.h"
#include "../../../Gimmick/Warp.h"
#include "../../../Engine/ResourceManager/CreateStage.h"

//コンストラクタ
WorldStage2::WorldStage2(GameObject* parent)
	:Stage(parent, "WorldStage2"), isStageDraw_(true)
{
	//画角
	ARGUMENT_INITIALIZE(fieldAngle_, 100);

	//ライトの強さ
	ARGUMENT_INITIALIZE(lightIntensity_, 2);
}

//初期化
void WorldStage2::Initialize()
{

	/////////////////ファイル読み込んでステージの各オブジェクト設置///////////////////

	//ステージ作成
	pCreateStage_ = new CreateStage;
	pCreateStage_->LoadFileCreateStage(this, "Stage/World/World2/StageInformation/WorldStage2.txt");

	/////////////////////モデルデータのロード///////////////////////

	hModel_[Base] = Model::Load("Stage/World/World2/Stage.fbx");
	hModel_[Space] = Model::Load("Stage/SpaceModel/Space.fbx");
	hModel_[PolyModel] = Model::Load("Stage/World/World2/Stage.fbx");

	///////////////////////////各種設定/////////////////////////////

	//レイの判定にBaseとRotationをいれたいのでtrueにしておく
	Model::SetRayFlag(hModel_[Base], true);

	//Spaceモデルの明るさ設定
	Model::SetBrightness(hModel_[Space], 1.0f);

	//PolyModelを透明に設定(軸を確認するためだけに使うため)
	Model::SetAlpha(hModel_[PolyModel], ZERO);

	//画角
	Camera::SetFieldAngle(fieldAngle_);

	//カメラの上ベクトル
	Camera::SetUpDirection(UP_VECTOR);

	//ライトの強さ
	Light::SetPlayerIntensity((float)lightIntensity_);

	//Warpの移動先
	ARGUMENT_INITIALIZE(warpPos_,XMFLOAT3(ZERO, 15.0f, ZERO));

	//Playerの初期位置
	ARGUMENT_INITIALIZE(pos_, XMFLOAT3(ZERO,204.5f, ZERO));

	//3Dなのでtrueにする
	ARGUMENT_INITIALIZE(threeDflag_,true);

	//球体使用しているのでtrue
	ARGUMENT_INITIALIZE(circleFlag_,true)
}

//更新
void WorldStage2::Update()
{
}

//描画
void WorldStage2::Draw()
{
	//ステージ描画するなら
	if (isStageDraw_)
	{
		Model::SetTransform(hModel_[Base], transform_);
		Model::Draw(hModel_[Base]);
	}

	Model::SetTransform(hModel_[Space], tSpace_);
	Model::Draw(hModel_[Space]);
}

//解放
void WorldStage2::Release()
{
}

//ムービー作成
void WorldStage2::CreateMovie()
{
	pCreateStage_->LoadFileCreateStage(this, "Stage/World/World2/StageInformation/WorldStage2_Movie.txt");
}

//ボスステージ作成
void WorldStage2::CreateBossStage()
{
	pCreateStage_->LoadFileCreateStage(this, "Stage/World/World2/StageInformation/WorldStage2_Boss.txt");
}

//ボス倒すシーン作成
void WorldStage2::CreateBossKill()
{
	pCreateStage_->LoadFileCreateStage(this, "Stage/World/World2/StageInformation/WorldStage2_BossKill.txt");
}