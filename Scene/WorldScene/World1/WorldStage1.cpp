#include "WorldStage1.h"
#include "../../../Engine/Model.h"
#include "../../../Engine/ImGuiSet.h"
#include "../../../Engine/Light.h"
#include "../../../Engine/Camera.h"
#include "../../../Gimmick/Warp.h"
#include "../../../Engine/CreateStage.h"

//コンストラクタ
WorldStage1::WorldStage1(GameObject* parent)
	:Stage(parent, "WorldStage1")
{
	//画角
	fieldAngle_ = 100;

	//ライトの強さ
	lightIntensity_ = 2;
}

//初期化
void WorldStage1::Initialize()
{
	/////////////////ステージ設置するために必要なGUI///////////////////

	Instantiate<ImGuiSet>(this);

	/////////////////ファイル読み込んでステージの各オブジェクト設置///////////////////

	//////ステージ作成
	CreateStage* pCreateStage = new CreateStage;
	pCreateStage->LoadFile(this,"Stage/World/World1/StageInformation/WorldStage1.txt");

	////ワープのシーン遷移先を決めておく
	//Warp* pWarp = (Warp*)FindObject("Warp");
	//pWarp->SetSceneId(SCENE_ID_TUTORIAL1);


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
	Model::SetAlpha(hModel_[PolyModel], 0);

	//画角
	Camera::SetFieldAngle(fieldAngle_);

	//カメラの上ベクトル
	Camera::SetUpDirection(XMVectorSet(0, 1, 0, 0));

	//ライトの強さ
	Light::SetPlayerIntensity(lightIntensity_);

	//Warpの移動先
	warpPos_ = { -70.5, 4.5, 76 };

	//Playerの初期位置
	pos_ = { -70.5,204.5,76 };

	//3Dなのでtrueにする
	threeDflag_ = true;

	//球体使用していないのでfalse
	circleFlag_ = false;

	//軸をMayaで設定したので差分を引く
	tRotation_.position_.x = -30;
	tRotation_.position_.z = 42;
}

//更新
void WorldStage1::Update()
{
	//モデル回転
	tRotation_.rotate_.y += 0.2;
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
