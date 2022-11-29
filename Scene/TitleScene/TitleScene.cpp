#include "TitleScene.h"
#include "../../Engine/Image.h"
#include "../../Engine/Input.h"
#include "../../Engine/SceneManager.h"
#include "../../Engine/Camera.h"
#include "../../Player.h"

//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene")
{

}

//初期化
void TitleScene::Initialize()
{
	Instantiate<Player>(this);

	///////////////画像データのロード///////////////////


	///////////////transform///////////////////


	///////////////カメラ///////////////////

	Camera::SetPosition(XMFLOAT3(0, 60, -50));
	Camera::SetTarget(XMFLOAT3(0, 10, 0));

}

//更新
void TitleScene::Update()
{

	//Aボタンを押したらPlayシーンへ移行
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
	{
	}

	//Padがないときに移行する用
	if (Input::IsKeyDown(DIK_RETURN))
	{
	}

}

//描画
void TitleScene::Draw()
{
}

//開放
void TitleScene::Release()
{
}

void TitleScene::StartUpdate()
{
}
