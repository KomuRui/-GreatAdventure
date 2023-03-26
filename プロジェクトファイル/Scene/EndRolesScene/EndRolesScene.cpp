#include "EndRolesScene.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../UI/EndRolesScene/EndRoles.h"
#include "../../Engine/ResourceManager/Audio.h"


//コンストラクタ
EndRolesScene::EndRolesScene(GameObject* parent)
	: GameObject(parent, "EndRolesScene"),hAudio_(-1)
{
}

//デストラクタ
EndRolesScene::~EndRolesScene()
{
	//音止める
	Audio::Stop(hAudio_);
}

//初期化
void EndRolesScene::Initialize()
{
	//エンドロール表示
	Instantiate<EndRoles>(this,"Image/EndRole/EndRoleImage.png","EndRoles");

	//フェードアウト
	Fade::SetFadeStatus(FADE_NORMAL_OUT);

	//音ロード
	hAudio_ = Audio::Load("Audio/BGM/EndRole/EndRole.wav");
	assert(hAudio_ >= ZERO);

	//音
	Audio::PlayLoop(hAudio_);
}

//更新
void EndRolesScene::Update()
{
}

//描画
void EndRolesScene::Draw()
{
}

//開放
void EndRolesScene::Release()
{
}

void EndRolesScene::StartUpdate()
{
}