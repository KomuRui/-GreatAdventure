#include "GameManager.h"
#include "../../Gimmick/Warp.h"
#include "../../Engine/Sprite.h"
#include "../../Engine/Time.h"
#include "../../Engine/Component/EasingMove.h"
#include "../../Engine/Easing.h"
#include "../../Engine/Light.h"
#include "../LifeManager/LifeManager.h"
#include "../CoinManager/CoinManager.h"
#include "../TextManager/TextManager.h"
#include "../MiniGameManager/MiniGameManager.h"
#include "../ButtonManager/ButtonManager.h"
#include "../../OtherObject/UserInfomation.h"
#include <cmath>

//定数
namespace
{
	//ファイルネームに必要な情報
	struct FNAME_LIST {
		int ID;
		std::string NAME;
	};

	//シーンのIDとファイルパスネームの設定
	static const FNAME_LIST FNAME[] = {
		{ SCENE_ID_TITLE, "Tutorial1Fade" },
		{ SCENE_ID_USER_SELECT, "Tutorial2Fade" },
		{ SCENE_ID_TUTORIAL1, "Tutorial1Fade" },
		{ SCENE_ID_TUTORIAL2, "Tutorial2Fade" },
		{ SCENE_ID_MINIGAME, "Tutorial2Fade" },
		{ SCENE_ID_MINIGAME_LEVEL_SELECT, "Tutorial2Fade" },
		{ SCENE_ID_HOME, "HomeFade" },
		{ SCENE_ID_WORLD1, "World1Fade" },
		{ SCENE_ID_WORLD2, "World2Fade" },
	};

	//ファイルパスに共通して必要なもの
	static const std::string PATH = "Image/Fade/";

	//フェードするときの加算する距離
	static const float FADE_ADD_DISTANCE = 10.0f; 
}

//ゲームのいろいろな管理をする
namespace GameManager
{
	///////////////////////////////変数//////////////////////////////////

	//フェードの状態:0 何もしない,1 フェードイン, 2フェードアウト 
	int FadeStatus_;

	//フェードで使用する最大距離
	float maxDistance_;

	//フェードで使用する今の距離
	float nowDistance_;

	//フェード用の画像(シーンの数分)
	Sprite* pSprite_[SCENE_ID_MAX];

	//ゲームオーバー用の画像
	Sprite* pGameOver_;
	EasingMove* pEasingScale_; //イージングするためのクラス(拡大縮小)
	EasingMove* pEasingRotate_;//イージングするためのクラス(回転)
	Transform GameOver_;       //ゲームオーバー画像用のトランスフォーム

	//現在使用されているプレイヤーのポインタ格納用
	PlayerBase* pNowPlayer_;

	//現在の使用されているステージのポインタ格納用
	Stage* pNowStage_;

	//現在の使用されているワープのポインタ格納用
	Warp* pNowWarp_;

	//シーンマネージャーのポインタ格納用
	SceneManager* pSceneManager_;

	//フェード用の画像の文字列(シーンの数分)
	std::string fadeImage_[SCENE_ID_MAX];

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

		//フェード用の画像ロード
		for (auto& f : FNAME) {
			ARGUMENT_INITIALIZE(pSprite_[f.ID], new Sprite);
			pSprite_[f.ID]->Load(PATH+f.NAME+".png");
		}

		//ゲームオーバー用の画像ロード
		ARGUMENT_INITIALIZE(pGameOver_,new Sprite);
		pGameOver_->Load("Image/Player/GameOver.png");

		//各変数初期化
		ARGUMENT_INITIALIZE(FadeStatus_, NOOP);
		ARGUMENT_INITIALIZE(pNowPlayer_, nullptr);
		ARGUMENT_INITIALIZE(pNowStage_, nullptr);
		ARGUMENT_INITIALIZE(pNowWarp_, nullptr);
		ARGUMENT_INITIALIZE(pSceneManager_, nullptr);
		ARGUMENT_INITIALIZE(maxDistance_,std::sqrt(pow((Direct3D::screenHeight_ / 2), 2) + pow((Direct3D::screenWidth_ / 2), 2)));
		ARGUMENT_INITIALIZE(nowDistance_, ZERO);
		ARGUMENT_INITIALIZE(pEasingScale_, new EasingMove(&GameOver_.scale_,XMFLOAT3(5,5,5),XMFLOAT3(1,1,1),4.0f, Easing::OutQuart));
		ARGUMENT_INITIALIZE(pEasingRotate_, new EasingMove(&GameOver_.rotate_,XMFLOAT3(0,0,720),XMFLOAT3(0,0,0),4.0f, Easing::OutQuart));
	}

	//シーン遷移の時の初期化
	void GameManager::SceneTransitionInitialize()
	{
		//いろいろ初期化状態にしておく
		Light::Initialize();
		MiniGameManager::Initialize();
		CoinManager::SceneTransitionInitialize();
		LifeManager::SceneTransitionInitialize();
		ARGUMENT_INITIALIZE(pEasingScale_, new EasingMove(&GameOver_.scale_, XMFLOAT3(5, 5, 5), XMFLOAT3(1, 1, 1), 4.0f, Easing::OutQuart));
		ARGUMENT_INITIALIZE(pEasingRotate_, new EasingMove(&GameOver_.rotate_, XMFLOAT3(0, 0, 720), XMFLOAT3(0, 0, 0), 4.0f, Easing::OutQuart));
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
		FadeDraw();
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

	//状態セット
	void GameManager::SetStatus(int status, std::string filename)
	{
		ARGUMENT_INITIALIZE(FadeStatus_,status);

		//状態によって分ける
		switch (FadeStatus_)
		{

		//画像だけ描画
		case DRAW:

			NormalDraw();
			break;

		//フェードイン
		case FADE_IN:

			ARGUMENT_INITIALIZE(nowDistance_, ZERO);
			break;

		//フェードアウト
		case FADE_OUT:

			ARGUMENT_INITIALIZE(nowDistance_, maxDistance_);
			break;

		//ゲームオーバー
		case GAME_OVER:

			pEasingScale_->Reset(&GameOver_.scale_, XMFLOAT3(5, 5, 5), XMFLOAT3(1, 1, 1), 4.0f, Easing::OutQuart);
			pEasingRotate_->Reset(&GameOver_.rotate_, XMFLOAT3(0, 0, 720), XMFLOAT3(0, 0, 0), 4.0f, Easing::OutQuart);
			break;

		//それ以外
		default:

			break;
		}
	}

	//状態ゲット
	int GameManager::GetStatus() { return FadeStatus_; }

	///////////////////////////////フェード用関数////////////////////////////////////

	//フェード描画
	void GameManager::FadeDraw()
	{
		//状態によって変える
		switch (FadeStatus_)
		{
			//画像だけ描画
			case DRAW:

				NormalDraw();
				break;

			//フェードイン
			case FADE_IN:

				FadeInDraw();
				break;

			//フェードアウト
			case FADE_OUT:

				FadeOutDraw();
				break;

				//ゲームオーバー
			case GAME_OVER:

				GameOverDraw();
				break;

			//それ以外
			default:

				break;
		}
	
	}

	//描画
	void GameManager::NormalDraw()
	{
		//画像用のtransform
		Transform t;

		//テクスチャのサイズ取得
		XMFLOAT3 size = pSprite_[pSceneManager_->GetSceneId()]->GetTextureSize();

		//切り抜き範囲をリセット（画像全体を表示する）
		RECT rect;
		rect.left = ZERO;
		rect.top = ZERO;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		//描画
		pSprite_[pSceneManager_->GetSceneId()]->Draw(t,rect);
	}

	//フェードイン描画
	void GameManager::FadeInDraw()
	{
		//画像用のtransform
		Transform t;

		//テクスチャのサイズ取得
		XMFLOAT3 size = pSprite_[pSceneManager_->GetSceneId()]->GetTextureSize();

		//切り抜き範囲をリセット（画像全体を表示する）
		RECT rect;
		rect.left = ZERO;
		rect.top = ZERO;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		nowDistance_ += FADE_ADD_DISTANCE;

		//描画
		pSprite_[pSceneManager_->GetSceneId()]->Draw(t, nowDistance_,rect);
	};

	//フェードアウト描画
	void GameManager::FadeOutDraw()
	{
		//画像用のtransform
		Transform t;

		//テクスチャのサイズ取得
		XMFLOAT3 size = pSprite_[pSceneManager_->GetSceneId()]->GetTextureSize();

		//切り抜き範囲をリセット（画像全体を表示する）
		RECT rect;
		rect.left = ZERO;
		rect.top = ZERO;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		nowDistance_ -= FADE_ADD_DISTANCE;

		if (nowDistance_ < ZERO)
			ARGUMENT_INITIALIZE(nowDistance_, ZERO);

		//描画
		pSprite_[pSceneManager_->GetSceneId()]->Draw(t, nowDistance_, rect);
	};

	//ゲームオーバー描画
	void GameManager::GameOverDraw()
	{
		//テクスチャのサイズ取得
		XMFLOAT3 size = pGameOver_->GetTextureSize();

		//動かす
		pEasingScale_->Move();
		bool f = pEasingRotate_->Move();

		//切り抜き範囲をリセット（画像全体を表示する）
		RECT rect;
		rect.left = ZERO;
		rect.top = ZERO;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		//描画
		pGameOver_->ReversalColorDraw(GameOver_, rect,XMFLOAT4(0.0f,0.0f, 0.0f,1.0f));

		//もしイージングの動きが終わっているのなら死んだ関数を呼ぶ
		if (f) PlayerDie();
	}
}