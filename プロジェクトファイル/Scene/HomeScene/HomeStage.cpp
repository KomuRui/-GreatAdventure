#include "HomeStage.h"
#include "../../Engine/Model.h"
#include "../../Engine/ImGuiSet.h"
#include "../../Engine/Light.h"
#include "../../Engine/Camera.h"
#include "../../Gimmick/Warp.h"
#include "../../Engine/CreateStage.h"

//コンストラクタ
HomeStage::HomeStage(GameObject* parent)
	:Stage(parent, "HomeStage")
{
	//画角
	fieldAngle_ = 100;

	//ライトの強さ
	lightIntensity_ = 3;
}

//初期化
void HomeStage::Initialize()
{
	/////////////////ステージ設置するために必要なGUI///////////////////

	Instantiate<ImGuiSet>(this);

	/////////////////ファイル読み込んでステージの各オブジェクト設置///////////////////

	//////ステージ作成
	CreateStage* pCreateStage = new CreateStage;
	pCreateStage->LoadFileCreateStage(this, "Stage/Home/StageInformation/HomeStage.txt");

	//ワープのシーン遷移先を決めておく
	Warp* pWarp = (Warp*)FindObject("Warp");
	pWarp->SetSceneId(SCENE_ID_WORLD1);

	////各ブロックの配置を取得
	tBlock_ = pCreateStage->GetTransformBlock();

	/////////////////////モデルデータのロード///////////////////////

	hModel_[Base] = Model::Load("Stage/Home/Home.fbx");
	hModel_[Space] = Model::Load("Stage/SpaceModel/Space.fbx");
	hModel_[PolyModel] = Model::Load("Stage/Home/Home_Polygon.fbx");

	///////////////////////////各種設定/////////////////////////////

	//レイの判定にBaseをいれたいのでtrueにしておく
	Model::SetRayFlag(hModel_[Base], true);

	//Spaceモデルの明るさ設定
	Model::SetBrightness(hModel_[Space], 0.5);

	//PolyModelを透明に設定(軸を確認するためだけに使うため)
	Model::SetAlpha(hModel_[PolyModel], 0);

	//画角
	Camera::SetFieldAngle(fieldAngle_);

	//カメラの上ベクトル
	Camera::SetUpDirection(XMVectorSet(0, 1, 0, 0));

	//ライトの強さ
	Light::SetPlayerIntensity(lightIntensity_);

	//Warpの移動先
	warpPos_ = { 0, 15, 0 };

	//Playerの初期位置
	pos_ = { 0,200,0 };

	//3Dなのでtrueにする
	threeDflag_ = true;

	//球体使用しているのでtrue
	circleFlag_ = true;

}

//更新
void HomeStage::Update()
{
	tSpace_.rotate_.y += 0.2;
}

//描画
void HomeStage::Draw()
{
	Model::SetTransform(hModel_[Base], transform_);
	Model::Draw(hModel_[Base]);

	Model::SetTransform(hModel_[Space], tSpace_);
	Model::Draw(hModel_[Space]);
}

//解放
void HomeStage::Release()
{
}
