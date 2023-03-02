#include "TutorialStage1.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Light.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Gimmick/Warp.h"
#include "../../Engine/ResourceManager/CreateStage.h"

//コンストラクタ
TutorialStage1::TutorialStage1(GameObject* parent)
	:Stage(parent,"TutorialStage1")
{
	//画角
	ARGUMENT_INITIALIZE(fieldAngle_,45);

	//ライトの強さ
	ARGUMENT_INITIALIZE(lightIntensity_,3);
}

//初期化
void TutorialStage1::Initialize()
{

	/////////////////ファイル読み込んでステージの各オブジェクト設置///////////////////

	//////ステージ作成
	pCreateStage_ = new CreateStage;
	pCreateStage_->LoadFileCreateStage(this, "Stage/Tutorial/StageInformation/TutorialStage1.txt");

	//ワープのシーン遷移先を決めておく
	Warp* pWarp = (Warp*)FindObject("Warp");
	pWarp->SetSceneId(SCENE_ID_TUTORIAL2);

	//各ブロックの配置を取得
	tBlock_ = pCreateStage_->GetTransformBlock();

	/////////////////////モデルデータのロード///////////////////////

	hModel_[Base] = Model::Load("Stage/Tutorial/first_1.fbx");
	hModel_[Space] = Model::Load("Stage/SpaceModel/Space.fbx");

	///////////////////////////各種設定/////////////////////////////

	//レイの判定にBaseをいれたいのでtrueにしておく
	Model::SetRayFlag(hModel_[Base], true);

	//Spaceモデルの明るさ設定
	Model::SetBrightness(hModel_[Space], 0.5);

	//画角
	Camera::SetFieldAngle(fieldAngle_);

	//カメラの上ベクトル
	Camera::SetUpDirection(XMVectorSet(0, 1, 0, 0));

	//ライトの強さ
	Light::SetPlayerIntensity(lightIntensity_);

	//Playerの初期位置
	pos_ = { 2,2,0 };

	//疑似2Dなのでfalseに設定しておく
	threeDflag_ = false;

	//球体使用していないのでfalse
	circleFlag_ = false;

}

//更新
void TutorialStage1::Update()
{
	tSpace_.rotate_.y += 0.1;
}

//描画
void TutorialStage1::Draw()
{
	Model::SetTransform(hModel_[Base], transform_);
	Model::Draw(hModel_[Base]);

	Model::SetTransform(hModel_[Space], tSpace_);
	Model::Draw(hModel_[Space]);
}

//解放
void TutorialStage1::Release()
{
}
