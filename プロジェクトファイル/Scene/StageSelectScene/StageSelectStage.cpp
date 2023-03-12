#include "StageSelectStage.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Light.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Gimmick/Warp.h"
#include "../../Engine/ResourceManager/CreateStage.h"

//コンストラクタ
StageSelectStage::StageSelectStage(GameObject* parent)
	:Stage(parent, "StageSelectStage")
{
	//画角
	ARGUMENT_INITIALIZE(fieldAngle_,45);
}

//初期化
void StageSelectStage::Initialize()
{

	/////////////////ファイル読み込んでステージの各オブジェクト設置///////////////////

	//////ステージ作成
	pCreateStage_ = new CreateStage;
	pCreateStage_->LoadFileCreateStage(this, "Stage/Home/StageInformation/StageSelectStage.txt");

	/////////////////////モデルデータのロード///////////////////////

	hModel_[Space] = Model::Load("Stage/SpaceModel/Space.fbx");

	///////////////////////////各種設定/////////////////////////////

	//Spaceモデルの明るさ設定
	Model::SetBrightness(hModel_[Space], 0.5f);

	//画角
	Camera::SetFieldAngle(fieldAngle_);

	//カメラの上ベクトル
	Camera::SetUpDirection(UP_VECTOR);
}

//更新
void StageSelectStage::Update()
{
}

//描画
void StageSelectStage::Draw()
{
	Model::SetTransform(hModel_[Space], tSpace_);
	Model::Draw(hModel_[Space]);
}

//解放
void StageSelectStage::Release()
{
}
