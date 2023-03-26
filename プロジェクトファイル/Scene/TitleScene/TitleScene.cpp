#include "TitleScene.h"
#include "../../Engine/ResourceManager/Image.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Player/PlayerBase.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Light.h"
#include "../../Engine/ResourceManager/CreateStage.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../Engine/ResourceManager/Audio.h"
#include "../../OtherObject/TitleModel.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Manager/MiniGameManager/MiniGameManager.h"
#include "../../Manager/AudioManager/OtherAudioManager/OtherAudioManager.h"

//定数
namespace
{
	static const float RATATION_SPEED = 0.5f;    //回転速度
	static const float BRIGHTNESS = 1.5f;		 //背景モデルの明るさ
	static const XMFLOAT3 CAM_POS = { 0, 0, 5 }; //カメラの位置
	static const XMFLOAT3 CAM_TAR = { 0, 0, 0 }; //カメラのターゲット
	static const int FIELD_ANGLE = 45;           //カメラの画角
}

//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hModel_(-1), hAudio_(-1), beforeTrrigerR_(ZERO)
{
}

//デストラクタ
TitleScene::~TitleScene()
{
	Audio::Stop(hAudio_);
}

//初期化
void TitleScene::Initialize()
{
	///////////////画像データのロード///////////////////

	hModel_ = Model::Load("Stage/Title/Model/BackGroundModel.fbx");
	assert(hModel_ >= ZERO);

	//背景のモデルを少し光らせる
	Model::SetBrightness(hModel_, BRIGHTNESS);


	/////////////////ファイル読み込んでステージの各オブジェクト設置///////////////////

	CreateStage* pCreateStage = new CreateStage;
	pCreateStage->LoadFileCreateStage(GetParent(), "Stage/Title/StageInformation/TitleScene1.txt");

	///////////////カメラ///////////////////

	Camera::SetPosition(CAM_POS);
	Camera::SetTarget(CAM_TAR);
	Camera::SetFieldAngle(FIELD_ANGLE);

	///////////////音///////////////////

	hAudio_ = Audio::Load("Audio/BGM/Title/Title.wav");
	assert(hAudio_ >= ZERO);

	Audio::PlayLoop(hAudio_);

	/////////////////フェードイン/////////////////////

	//もし前回のシーンがタイトルじゃないのならフェードイン
	if (GameManager::GetpSceneManager()->GetBeforeSceneId() != SCENE_ID_TITLE)
		Fade::SetFadeStatus(FADE_CIRCLE_IN);
}

//更新の前に一度だけ呼ばれる更新
void TitleScene::StartUpdate()
{
}

//更新
void TitleScene::Update()
{
	//背景回転させる
	transform_.rotate_.y += RATATION_SPEED;

	//AとRトリガー同時押しでシーン移動(タイムメソッドが使われていないのなら)
	if (Input::IsPadButton(XINPUT_GAMEPAD_A) && Input::GetPadTrrigerR() && !GetTimeMethod())
	{
		//シーン移動の際のエフェクト表示
		TitleModel* pTitleModel = (TitleModel*)FindObject("TitleModel");

		//nullptrじゃなければ
		if(pTitleModel !=nullptr)
			pTitleModel->SceneChangeEffect();

		//音
		OtherAudioManager::ClickAudio();

		//エフェクトが広がったときにシーン移行したいのでタイムメソッドを使って指定した時間がたったころに呼ぶ
		SetTimeMethod(0.5f);
	}

	//Aかトリガーを押したのなら
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) || (Input::GetPadTrrigerR() && beforeTrrigerR_ == ZERO))
	{
		//音
		OtherAudioManager::ClickAudio();
	}

	//前回の入力を保存
	ARGUMENT_INITIALIZE(beforeTrrigerR_, Input::GetPadTrrigerR());

}

//描画
void TitleScene::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void TitleScene::Release()
{
}

//指定した時間で呼ばれるメソッド
void TitleScene::TimeMethod()
{
	//ロードの時の描画を設定しない
	GameManager::GetpSceneManager()->SetLoadDrawFlag(false);
	GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_USER_SELECT);
}