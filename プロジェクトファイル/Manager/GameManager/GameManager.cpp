#include "GameManager.h"
#include "../../Gimmick/Warp.h"
#include "../../Engine/DirectX/Sprite.h"
#include "../../Engine/ResourceManager/Time.h"
#include "../../Engine/Component/EasingMove.h"
#include "../../Engine/ResourceManager/Easing.h"
#include "../../Engine/GameObject/Light.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../Engine/ResourceManager/Image.h"
#include "../LifeManager/LifeManager.h"
#include "../CoinManager/CoinManager.h"
#include "../TextManager/TextManager.h"
#include "../MiniGameManager/MiniGameManager.h"
#include "../ButtonManager/ButtonManager.h"
#include "../AudioManager/CoinAudioManager/CoinAudioMAnager.h"
#include "../AudioManager/PlayerAudioManager/PlayerAudioManager.h"
#include "../AudioManager/OtherAudioManager/OtherAudioManager.h"
#include "../../OtherObject/UserInfomation.h"
#include "../../OtherObject/SelectPlanetController.h"
#include "../../UI/Pause/PauseUI.h"
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

	//ポーズの時に表示するUI
	PauseUI* pPauseUI_;

	///////////////////////////////関数//////////////////////////////////

	//初期化
	void GameManager::Initialize()
	{
		//ユーザー情報の初期化
		UserInfomation::Initialize();

		//ユーザー選択シーン管理の初期化
		SelectPlanetController::Initialize();

		CoinAudioManager::Initialize();
		OtherAudioManager::Initialize();
		PlayerAudioManager::Initialize();

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
		ARGUMENT_INITIALIZE(pPauseUI_, new PauseUI);
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
		CoinAudioManager::SceneTransitionInitialize();
		OtherAudioManager::SceneTransitionInitialize();
		PlayerAudioManager::SceneTransitionInitialize();
		ARGUMENT_INITIALIZE(pPauseUI_, new PauseUI);
		CoinManager::KeepCoinUpdate();
	}

	//Playerが死亡した時にLifeManagerから呼ばれる
	void GameManager::PlayerDie()
	{
		//ライフ元通りに
		LifeManager::ResetLife();

		//もしボスのシーンならコインを初期化状態に
		if (pSceneManager_->GetSceneId() == SCENE_ID_WORLD2) CoinManager::SetCoinKeep();

		//もし死んだシーンがチュートリアルシーンなら
		if(pSceneManager_->GetSceneId() == SCENE_ID_TUTORIAL1 || pSceneManager_->GetSceneId() == SCENE_ID_TUTORIAL2)
			pSceneManager_->SameSceneInitializ(SCENE_ID_TUTORIAL1);
		//ミニゲームにかかわるシーンなら
		else if(pSceneManager_->GetSceneId() == SCENE_ID_MINIGAME || pSceneManager_->GetSceneId() == SCENE_ID_MINIGAME_LEVEL_SELECT)
			pSceneManager_->SameSceneInitializ(SCENE_ID_MINIGAME_LEVEL_SELECT);
		//それ以外なら
		else
			pSceneManager_->SameSceneInitializ(SCENE_ID_HOME);
	}

	//更新
	void GameManager::Update()
	{
		//スタートボタンを押したかつまだポーズ画面を描画していないかつ任意のシーンじゃないのならポーズ画面のUI作成
		if (Input::IsPadButtonDown(XINPUT_GAMEPAD_START) && !pPauseUI_->isDrawUI()
			&& pSceneManager_->GetSceneId() != SCENE_ID_ENDROLES
			&& pSceneManager_->GetSceneId() != SCENE_ID_MINIGAME
			&& pSceneManager_->GetSceneId() != SCENE_ID_TITLE
			&& pSceneManager_->GetSceneId() != SCENE_ID_USER_SELECT) {
			pPauseUI_->CreateUI(); 
			Direct3D::SetTimeScale(true);
			OtherAudioManager::ClickAudio();
		}

		//ポーズ画面の更新を呼ぶ
		pPauseUI_->Update();

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

		//Uiなどを表示
		Image::UiDraw();
		
		//ポーズ画面の描画
		pPauseUI_->Draw();

		//フェード用の描画
		Fade::Draw();
	}

	/// <summary>
	/// ポーズ画面を削除
	/// </summary>
	void GameManager::PauseDelete()
	{
		pPauseUI_->AllRelease();
		Direct3D::SetTimeScale(false);
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