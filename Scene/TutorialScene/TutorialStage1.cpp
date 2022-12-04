#include "TutorialStage1.h"
#include "../../Engine/Model.h"
#include "../../Engine/ImGuiSet.h"
#include "../../Engine/Light.h"
#include "../../Engine/Camera.h"
#include "../../Gimmick/Warp.h"

//コンストラクタ
TutorialStage1::TutorialStage1(GameObject* parent)
	:Stage(parent,"TutorialStage1")
{
	//画角
	fieldAngle_ = 45;

	//ライトの強さ
	lightIntensity_ = 3;
}

//初期化
void TutorialStage1::Initialize()
{
	/////////////////ステージの各オブジェクト設置///////////////////

	//ステージ作成
	ImGuiSet* a = Instantiate<ImGuiSet>(this);
	a->CreateStage("Stage/Tutorial/StageInformation/TutorialStage1.txt");

	//ワープのシーン遷移先を決めておく
	Warp* pWarp = (Warp*)FindObject("Warp");
	pWarp->SetSceneId(SCENE_ID_TUTORIAL2);

	//各ブロックの配置を取得
	tBlock_ = a->GetTransformBlock();

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
	Light::SetIntensity(lightIntensity_);

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
