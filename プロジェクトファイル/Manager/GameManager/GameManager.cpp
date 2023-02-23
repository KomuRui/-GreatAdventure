#include "GameManager.h"
#include "../../Gimmick/Warp.h"
#include "../../Engine/DirectX/Sprite.h"
#include "../../Engine/ResourceManager/Time.h"
#include "../../Engine/Component/EasingMove.h"
#include "../../Engine/ResourceManager/Easing.h"
#include "../../Engine/GameObject/Light.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../LifeManager/LifeManager.h"
#include "../CoinManager/CoinManager.h"
#include "../TextManager/TextManager.h"
#include "../MiniGameManager/MiniGameManager.h"
#include "../ButtonManager/ButtonManager.h"
#include "../../OtherObject/UserInfomation.h"
#include <cmath>

//ゲームのいろいろな管理をする
namespace GameManager
{
	///////////////////////////////変数//////////////////////////////////

	//現在使用されているプレイヤーのポインタ格納用
	PlayerBase* pNowPlayer_;

	//現在の使用されているステージのポインタ格納用
	Stage* pNowStage_;

	//現在の使用されているワープのポインタ格納用
	Warp* pNowWarp_;

	//シーンマネージャーのポインタ格納用
	SceneManager* pSceneManager_;

	///////////////////////////////関数//////////////////////////////////

	//初期化
	void GameManager::Initialize()
	{
		//ユーザー情報の初期化
		UserInfomation::Initialize();

		//ライフマネージャーの初期化
		LifeManager::Initialize();

		//コインマネージャーの初期化
		CoinManager::Initialize();

		//テキストマネージャの初期化
		TextManager::Initialize();

		//ミニゲームマネージャーの初期化
		MiniGameManager::Initialize();

		//フェイドの初期化
		Fade::Initialize();

		//各変数初期化
		ARGUMENT_INITIALIZE(pNowPlayer_, nullptr);
		ARGUMENT_INITIALIZE(pNowStage_, nullptr);
		ARGUMENT_INITIALIZE(pNowWarp_, nullptr);
		ARGUMENT_INITIALIZE(pSceneManager_, nullptr);
	}

	//シーン遷移の時の初期化
	void GameManager::SceneTransitionInitialize()
	{
		//いろいろ初期化状態にしておく
		Light::Initialize();
		Fade::SceneTransitionInitialize();
		MiniGameManager::Initialize();
		CoinManager::SceneTransitionInitialize();
		LifeManager::SceneTransitionInitialize();
	}

	//Playerが死亡した時にLifeManagerから呼ばれる
	void GameManager::PlayerDie()
	{
		//ライフ元通りに
		LifeManager::ResetLife();

		//もし死んだシーンがチュートリアルシーンなら
		if(pSceneManager_->GetSceneId() == SCENE_ID_TUTORIAL1 || pSceneManager_->GetSceneId() == SCENE_ID_TUTORIAL2)
			pSceneManager_->ChangeScene(SCENE_ID_TUTORIAL1);
		else
			pSceneManager_->ChangeScene(SCENE_ID_HOME);
	}

	//更新
	void GameManager::Update()
	{
		//ボタンマネージャの更新を呼ぶ
		ButtonManager::Update();
	}

	//描画(コインの取得数やPlayerライフの表示)
	void GameManager::Draw()
	{
		//もしミニゲームなら
		if (pSceneManager_->GetSceneId() == SCENE_ID_MINIGAME)
		{
			//ミニゲームの各情報を描画
			MiniGameManager::Draw();

			//コインの取得数の表示
			CoinManager::Draw();
		}
		//もしPlayシーンなら
		else if (pSceneManager_->GetSceneId() != SCENE_ID_TITLE && pSceneManager_->GetSceneId() != SCENE_ID_USER_SELECT)
		{
			//Playerライフの表示
			LifeManager::Draw();

			//コインの取得数の表示
			CoinManager::Draw();
		}
			
		//フェード用の描画
		Fade::Draw();
	}

	///////////////////////////////セットゲット関数//////////////////////////////////
	
	//プレイヤーのポインタセット
	void GameManager::SetpPlayer(PlayerBase* player) { pNowPlayer_ = player; }

	//プレイヤーのポインタゲット
	PlayerBase* GameManager::GetpPlayer() { return pNowPlayer_; }

	//ステージのポインタセット
	void GameManager::SetpStage(Stage* stage) { pNowStage_ = stage; }

	//ステージのポインタゲット
	Stage* GameManager::GetpStage() { return pNowStage_; }

	//ワープのポインタセット
	void GameManager::SetpWarp(Warp* warp) { pNowWarp_ = warp; }

	//ワープのポインタゲット
	Warp* GameManager::GetpWarp() { return pNowWarp_; }

	//シーンマネージャーのポインタセット
	void GameManager::SetpSceneManager(SceneManager* scene) { pSceneManager_ = scene; }

	//シーンマネージャーのポインタゲット
	SceneManager* GameManager::GetpSceneManager() { return pSceneManager_; }

}