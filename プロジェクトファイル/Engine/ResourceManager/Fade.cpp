#include "Fade.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../DirectX/Sprite.h"
#include "../Component/EasingMove.h"
#include "Easing.h"
#include "../../Manager/GameManager/GameManager.h"

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

//フェードを行うときに使う(大体１度に１回しか使われないのでnamespace)
namespace Fade
{

	///////////////////////////////変数//////////////////////////////////

	int FadeStatus_;    //フェードの状態
	float maxDistance_; //円フェードで使用する最大距離
	float nowDistance_; //フェードで使用する今の距離

	//フェード用の画像(シーンの数分)
	Sprite* pSprite_[SCENE_ID_MAX];

	//ゲームオーバーフェイド用の画像
	Sprite* pGameOver_;
	EasingMove* pEasingScale_; //イージングするためのクラス(拡大縮小)
	EasingMove* pEasingRotate_;//イージングするためのクラス(回転)
	Transform GameOver_;       //ゲームオーバー画像用のトランスフォーム

	//フェード用の画像の文字列(シーンの数分)
	std::string fadeImage_[SCENE_ID_MAX];

	///////////////////////////////関数//////////////////////////////////

	//初期化
	void Fade::Initialize()
	{
		//フェード用の画像ロード
		for (auto& f : FNAME) {
			ARGUMENT_INITIALIZE(pSprite_[f.ID], new Sprite);
			pSprite_[f.ID]->Load(PATH + f.NAME + ".png");
		}

		//ゲームオーバー用の画像ロード
		ARGUMENT_INITIALIZE(pGameOver_, new Sprite);
		pGameOver_->Load("Image/Player/GameOver.png");

		//各変数初期化
		ARGUMENT_INITIALIZE(FadeStatus_, NOOP);
		ARGUMENT_INITIALIZE(maxDistance_, std::sqrt(pow((Direct3D::screenHeight_ / 2), 2) + pow((Direct3D::screenWidth_ / 2), 2)));
		ARGUMENT_INITIALIZE(nowDistance_, ZERO);
	}

	//シーン遷移の時の初期化
	void Fade::SceneTransitionInitialize()
	{
		//いろいろ初期化状態にしておく
		ARGUMENT_INITIALIZE(pEasingScale_, new EasingMove(&GameOver_.scale_, XMFLOAT3(5, 5, 5), XMFLOAT3(1, 1, 1), 4.0f, Easing::OutQuart));
		ARGUMENT_INITIALIZE(pEasingRotate_, new EasingMove(&GameOver_.rotate_, XMFLOAT3(0, 0, 720), XMFLOAT3(0, 0, 0), 4.0f, Easing::OutQuart));
	}

	//描画
	void Fade::Draw()
	{
		//フェード用の描画
		FadeDraw();
	}

	///////////////////////////////セットゲット関数//////////////////////////////////

	//状態セット
	void Fade::SetFadeStatus(int status, std::string filename)
	{
		ARGUMENT_INITIALIZE(FadeStatus_, status);

		//状態によって分ける
		switch (FadeStatus_)
		{

			//画像だけ描画
		case DRAW:

			NormalDraw();
			break;

			//フェードイン
		case FADE_CIRCLE_IN:

			ARGUMENT_INITIALIZE(nowDistance_, ZERO);
			break;

			//フェードアウト
		case FADE_CIRCLE_OUT:

			ARGUMENT_INITIALIZE(nowDistance_, maxDistance_);
			break;

			//ゲームオーバー
		case FADE_GAME_OVER:

			pEasingScale_->Reset(&GameOver_.scale_, XMFLOAT3(5, 5, 5), XMFLOAT3(1, 1, 1), 4.0f, Easing::OutQuart);
			pEasingRotate_->Reset(&GameOver_.rotate_, XMFLOAT3(0, 0, 720), XMFLOAT3(0, 0, 0), 4.0f, Easing::OutQuart);
			break;

			//それ以外
		default:

			break;
		}
	}

	//状態ゲット
	int Fade::GetFadeStatus() { return FadeStatus_; }

	///////////////////////////////フェード用関数////////////////////////////////////

	//フェード描画
	void Fade::FadeDraw()
	{
		//状態によって変える
		switch (FadeStatus_)
		{
			//画像だけ描画
		case DRAW:

			NormalDraw();
			break;

			//フェードイン
		case FADE_CIRCLE_IN:

			FadeInCircleDraw();
			break;

			//フェードアウト
		case FADE_CIRCLE_OUT:

			FadeOutCircleDraw();
			break;

			//ゲームオーバー
		case FADE_GAME_OVER:

			GameOverDraw();
			break;

			//それ以外
		default:

			break;
		}

	}

	//描画
	void Fade::NormalDraw()
	{
		//画像用のtransform
		Transform t;

		//テクスチャのサイズ取得
		XMFLOAT3 size = pSprite_[GameManager::GetpSceneManager()->GetSceneId()]->GetTextureSize();

		//切り抜き範囲をリセット（画像全体を表示する）
		RECT rect;
		rect.left = ZERO;
		rect.top = ZERO;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		//描画
		pSprite_[GameManager::GetpSceneManager()->GetSceneId()]->Draw(t, rect);
	}

	//フェードイン描画
	void Fade::FadeInCircleDraw()
	{
		//画像用のtransform
		Transform t;

		//テクスチャのサイズ取得
		XMFLOAT3 size = pSprite_[GameManager::GetpSceneManager()->GetSceneId()]->GetTextureSize();

		//切り抜き範囲をリセット（画像全体を表示する）
		RECT rect;
		rect.left = ZERO;
		rect.top = ZERO;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		nowDistance_ += FADE_ADD_DISTANCE;

		//描画
		pSprite_[GameManager::GetpSceneManager()->GetSceneId()]->Draw(t, nowDistance_, rect);
	};

	//フェードアウト描画
	void Fade::FadeOutCircleDraw()
	{
		//画像用のtransform
		Transform t;

		//テクスチャのサイズ取得
		XMFLOAT3 size = pSprite_[GameManager::GetpSceneManager()->GetSceneId()]->GetTextureSize();

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
		pSprite_[GameManager::GetpSceneManager()->GetSceneId()]->Draw(t, nowDistance_, rect);
	};

	//ゲームオーバー描画
	void Fade::GameOverDraw()
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
		pGameOver_->ReversalColorDraw(GameOver_, rect, XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

		//もしイージングの動きが終わっているのなら死んだ関数を呼ぶ
		if (f) GameManager::PlayerDie();
	}


}
