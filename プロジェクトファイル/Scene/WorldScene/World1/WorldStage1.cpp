#include "WorldStage1.h"
#include "../../../Engine/ResourceManager/Model.h"
#include "../../../Engine/GameObject/Light.h"
#include "../../../Engine/GameObject/Camera.h"
#include "../../../Gimmick/Warp.h"
#include "../../../Engine/ResourceManager/CreateStage.h"

//コンストラクタ
WorldStage1::WorldStage1(GameObject* parent)
	:Stage(parent, "WorldStage1")
{
	//画角
	ARGUMENT_INITIALIZE(fieldAngle_,100);

	//ライトの強さ
	ARGUMENT_INITIALIZE(lightIntensity_, 2);
}

//初期化
void WorldStage1::Initialize()
{

	/////////////////ファイル読み込んでステージの各オブジェクト設置///////////////////

	//ステージ作成
	pCreateStage_ = new CreateStage;
	pCreateStage_->LoadFileCreateStage(this,"Stage/World/World1/StageInformation/WorldStage1.txt");

	//ワープのシーン遷移先を決めておく
	Warp* pWarp = (Warp*)FindObject("Warp");
	pWarp->SetSceneId(SCENE_ID_HOME);
	pWarp->SetStageRelease(3); //このステージをクリアしたら解放ステージ数が3になるようにする

	/////////////////////モデルデータのロード///////////////////////

	hModel_[Base] = Model::Load("Stage/World/World1/Stage_Main.fbx");
	hModel_[Space] = Model::Load("Stage/SpaceModel/Space1.fbx");
	hModel_[PolyModel] = Model::Load("Stage/World/World1/Stage_Hit_Test.fbx");
	Model_[Rotation] = Model::Load("Stage/World/World1/Stage_Rotation.fbx");

	///////////////////////////各種設定/////////////////////////////

	//レイの判定にBaseとRotationをいれたいのでtrueにしておく
	Model::SetRayFlag(hModel_[Base], true);
	Model::SetRayFlag(Model_[Rotation], true);

	//Spaceモデルの明るさ設定
	Model::SetBrightness(hModel_[Space], 0.5f);

	//PolyModelを透明に設定(軸を確認するためだけに使うため)
	Model::SetAlpha(hModel_[PolyModel], ZERO);

	//画角
	Camera::SetFieldAngle(fieldAngle_);

	//カメラの上ベクトル
	Camera::SetUpDirection(UP_VECTOR);

	//ライトの強さ
	Light::SetPlayerIntensity((float)lightIntensity_);

	//Warpの移動先
	ARGUMENT_INITIALIZE(warpPos_,XMFLOAT3(-70.5, 4.5, 76));

	//Playerの初期位置
	ARGUMENT_INITIALIZE(pos_, XMFLOAT3(-70.5,204.5,76));

	//3Dなのでtrueにする
	ARGUMENT_INITIALIZE(threeDflag_,true);

	//球体使用していないのでfalse
	ARGUMENT_INITIALIZE(circleFlag_,false);

	//軸をMayaで設定したので差分を引く
	ARGUMENT_INITIALIZE(tRotation_.position_.x, -30);
	ARGUMENT_INITIALIZE(tRotation_.position_.z, 42);
}

//更新
void WorldStage1::Update()
{
	//モデル回転
	tRotation_.rotate_.y += 0.2f;
}

//描画
void WorldStage1::Draw()
{
	Model::SetTransform(hModel_[Base], transform_);
	Model::Draw(hModel_[Base]);

	Model::SetTransform(Model_[Rotation], tRotation_);
	Model::Draw(Model_[Rotation]);

	Model::SetTransform(hModel_[Space], tSpace_);
	Model::Draw(hModel_[Space]);
}

//解放
void WorldStage1::Release()
{
}
