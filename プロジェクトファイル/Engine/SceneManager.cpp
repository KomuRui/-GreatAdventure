#include "sceneManager.h"
#include "Model.h"
#include "Image.h"
#include "Audio.h"
#include "Light.h"
#include "../Scene/TitleScene/TitleScene.h"
#include "../Scene/TutorialScene/TutorialScene1.h"
#include "../Scene/TutorialScene/TutorialScene2.h"
#include "../Scene/HomeScene/HomeScene.h"
#include "../Scene/WorldScene/World1/WorldScene1.h"
#include "../Engine/GameManager.h"
#include "../Scene/UserSelectScene/UserSelectScene.h"

//コンストラクタ
SceneManager::SceneManager(GameObject * parent)
	: GameObject(parent, "SceneManager"), loadDrawFlag_(true)
{
}

//初期化
void SceneManager::Initialize()
{
	//最初のシーンを準備
	currentSceneID_ = SCENE_ID_WORLD1;
	nextSceneID_ = currentSceneID_;
	Instantiate<WorldScene1>(this);
}

//更新
void SceneManager::Update()
{
	//次のシーンが現在のシーンと違う　＝　シーンを切り替えなければならない
	if (currentSceneID_ != nextSceneID_)
	{
		//ロード中に描画するなら
		if (loadDrawFlag_)
		{
			//ロードしているとき用の画像表示(すぐ表示したいので描画終了を呼ぶ)
			GameManager::SetStatus(DRAW);
			Direct3D::EndDraw();
		}

		//そのシーンのオブジェクトを全削除
		KillAllChildren();

		//ロードしたデータを全削除
		Audio::AllRelease();
		Model::AllRelease();
		Image::AllRelease();

		//ライトを初期化状態にしておく
		Light::Initialize();

		//次のシーンを作成
		switch (nextSceneID_)
		{
		case SCENE_ID_TITLE:				 Instantiate<TitleScene>(this); break;
		case SCENE_ID_USER_SELECT:			 Instantiate<UserSelectScene>(this); break;
		case SCENE_ID_TUTORIAL1:		     Instantiate<TutorialScene1>(this); break;
		case SCENE_ID_TUTORIAL2:		     Instantiate<TutorialScene2>(this); break;
		case SCENE_ID_HOME:     		     Instantiate<HomeScene>(this); break;
		case SCENE_ID_WORLD1:                Instantiate<WorldScene1>(this); break;
		}
		currentSceneID_ = nextSceneID_;

		//ロード中に描画するに初期化しておく
		ARGUMENT_INITIALIZE(loadDrawFlag_, true);
	}

}

//描画
void SceneManager::Draw()
{
}

//開放
void SceneManager::Release()
{
}

void SceneManager::StartUpdate()
{
}

//シーン切り替え（実際に切り替わるのはこの次のフレーム）
void SceneManager::ChangeScene(SCENE_ID next)
{
	nextSceneID_ = next;

}

//現在のシーンIDゲット
SCENE_ID SceneManager::GetSceneId()
{
	return nextSceneID_;
}

//ロードをしてる時に画像表示するかセットする
void SceneManager::SetLoadDrawFlag(bool flag)
{
	ARGUMENT_INITIALIZE(loadDrawFlag_, flag);
}