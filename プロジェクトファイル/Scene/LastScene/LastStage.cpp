#include "LastStage.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Light.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Gimmick/Warp.h"
#include "../../Engine/ResourceManager/CreateStage.h"

//コンストラクタ
LastStage::LastStage(GameObject* parent)
	:Stage(parent, "LastStage")
{
	//画角
	ARGUMENT_INITIALIZE(fieldAngle_,100);

	//ライトの強さ
	ARGUMENT_INITIALIZE(lightIntensity_,3);
}

//初期化
void LastStage::Initialize()
{

	/////////////////ファイル読み込んでステージの各オブジェクト設置///////////////////

	//////ステージ作成
	//pCreateStage_ = new CreateStage;
	//pCreateStage_->LoadFileCreateStage(this, "Stage/Last/StageInformation/LastStage.txt");


	/////////////////////モデルデータのロード///////////////////////

	hModel_[Base] = Model::Load("Stage/Last/LastStage.fbx");
	hModel_[Space] = Model::Load("Stage/SpaceModel/Space.fbx");
	hModel_[PolyModel] = Model::Load("Stage/Last/LastStage.fbx");

	///////////////////////////各種設定/////////////////////////////

	//レイの判定にBaseをいれたいのでtrueにしておく
	Model::SetRayFlag(hModel_[Base], true);

	//Spaceモデルの明るさ設定
	Model::SetBrightness(hModel_[Space], 0.5f);

	//PolyModelを透明に設定(軸を確認するためだけに使うため)
	Model::SetAlpha(hModel_[PolyModel], ZERO);

	//画角
	Camera::SetFieldAngle(fieldAngle_);

	//カメラの上ベクトル
	Camera::SetUpDirection(UP_VECTOR);

	//ライトの強さ
	Light::SetPlayerIntensity(lightIntensity_);

	//Playerの初期位置
	pos_ = { 0,4,0 };

	//3Dなのでtrueにする
	ARGUMENT_INITIALIZE(threeDflag_,true);

	//球体使用しているのでtrue
	ARGUMENT_INITIALIZE(circleFlag_,true);

}

//更新
void LastStage::Update()
{
	tSpace_.rotate_.y += 0.2;
}

//描画
void LastStage::Draw()
{
	Model::SetTransform(hModel_[Base], transform_);
	Model::Draw(hModel_[Base]);

	Model::SetTransform(hModel_[Space], tSpace_);
	Model::Draw(hModel_[Space]);
}

//解放
void LastStage::Release()
{
}
