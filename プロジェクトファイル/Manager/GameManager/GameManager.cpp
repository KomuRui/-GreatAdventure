#include "GameManager.h"
#include "../../Engine/Sprite.h"
#include "../LifeManager/LifeManager.h"
#include "../CoinManager/CoinManager.h"
#include <cmath>

//定数
namespace
{
	static const float FADE_ADD_DISTANCE = 10.0f; //フェードするときの加算する距離
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

	//現在使用されているプレイヤーのポインタ格納用
	Player* pNowPlayer_;

	//現在の使用されているステージのポインタ格納用
	Stage* pNowStage_;

	//シーンマネージャーのポインタ格納用
	SceneManager* pSceneManager_;

	//フェード用の画像の文字列(シーンの数分)
	std::string fadeImage_[SCENE_ID_MAX];

	///////////////////////////////関数//////////////////////////////////

	//初期化
	void GameManager::Initialize()
	{
		//ライフマネージャーの初期化
		LifeManager::Initialize();

		//コインマネージャーの初期化
		CoinManager::Initialize();

		//変数初期化
		fadeImage_[SCENE_ID_TITLE] = "Image/Fade/Tutorial1Fade.png";
		fadeImage_[SCENE_ID_USER_SELECT] = "Image/Fade/Tutorial2Fade.png";
		fadeImage_[SCENE_ID_TUTORIAL1] = "Image/Fade/Tutorial1Fade.png";
		fadeImage_[SCENE_ID_TUTORIAL2] = "Image/Fade/Tutorial2Fade.png";
		fadeImage_[SCENE_ID_HOME] = "Image/Fade/HomeFade.png";
		fadeImage_[SCENE_ID_WORLD1] = "Image/Fade/World1Fade.png";
		ARGUMENT_INITIALIZE(FadeStatus_, NOOP);
		ARGUMENT_INITIALIZE(pNowPlayer_, nullptr);
		ARGUMENT_INITIALIZE(pNowStage_, nullptr);
		ARGUMENT_INITIALIZE(maxDistance_,std::sqrt(pow((Direct3D::screenHeight_ / 2), 2) + pow((Direct3D::screenWidth_ / 2), 2)));
		ARGUMENT_INITIALIZE(nowDistance_, 0);

		//フェード用の画像ロード
		for (int i = 0; i < SCENE_ID_MAX; i++)
		{
			ARGUMENT_INITIALIZE(pSprite_[i], new Sprite);
			pSprite_[i]->Load(fadeImage_[i]);
		}
	}

	//Playerが死亡した時にLifeManagerから呼ばれる
	void GameManager::PlayerDie()
	{

	}

	/// <summary>
	/// 描画(コインの取得数やPlayerライフの表示)
	/// </summary>
	void Draw()
	{
		//Playerライフの表示
		LifeManager::Draw();

		//コインの取得数の表示
		CoinManager::Draw();

		//フェード用の描画
		FadeDraw();
	}

	///////////////////////////////セットゲット関数//////////////////////////////////
	
	//プレイヤーのポインタセット
	void GameManager::SetpPlayer(Player* player) { pNowPlayer_ = player; }

	//プレイヤーのポインタゲット
	Player* GameManager::GetpPlayer() { return pNowPlayer_; }

	//ステージのポインタセット
	void GameManager::SetpStage(Stage* stage) { pNowStage_ = stage; }

	//ステージのポインタゲット
	Stage* GameManager::GetpStage() { return pNowStage_; }

	//シーンマネージャーのポインタセット
	void GameManager::SetpSceneManager(SceneManager* scene) { pSceneManager_ = scene; }

	//シーンマネージャーのポインタゲット
	SceneManager* GameManager::GetpSceneManager() { return pSceneManager_; }

	//状態セット
	void GameManager::SetStatus(int status)
	{
		FadeStatus_ = status;

		//状態によって分ける
		switch (FadeStatus_)
		{
			//画像だけ描画
		case DRAW:

			NormalDraw();

			//フェードイン
		case FADE_IN:

			ARGUMENT_INITIALIZE(nowDistance_, ZERO);
			break;

			//フェードアウト
		case FADE_OUT:

			ARGUMENT_INITIALIZE(nowDistance_, maxDistance_);
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
}