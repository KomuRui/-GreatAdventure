#include "LifeManager.h"
#include "../../Engine/Global.h"
#include "../GameManager/GameManager.h"
#include "../../Engine/Sprite.h"
#include "../../Engine/Transform.h"
#include "../../Engine/Text.h"

//定数
namespace
{
	//ライフ
	static const int NORMAL_PLAYER_LIFE = 3; //普通のPlayerのライフの数

	//拡大縮小
	static const XMFLOAT3 NORMAL_SCALE = { 1.0f,1.0f,1.0f }; //通常拡大率
	static const XMVECTOR MIN_SCALE = { 1.0f,1.0f,1.0f };    //最低拡大率
	static const XMVECTOR MAX_SCALE = { 1.1f,1.1f,1.0f };    //最高拡大率
	static const float NORMAL_INTERPOLATION_FACTOR = 0.2f;   //通常補間係数
	static const float ONELIFE_INTERPOLATION_FACTOR = 0.4f;  //1ライフしかないときの補間係数
	static const float CHANGE_TARGET_DISTANCE = 0.005f;      //ターゲット変更するときの距離
}

/// <summary>
/// Playerのライフ管理
/// </summary>
namespace LifeManager
{
	/// <summary>
	/// ライフごとに画像を分けたいので列挙する
	/// </summary>
	enum Life
	{
		Zero,		//HP0
		One,		//HP1
		Two,		//HP2
		Three,		//HP3
		MAX_LIFE_IMAGE
	};

	///////////////////////////////変数//////////////////////////////////

	//Playerの現在のライフの総数
	int playerLife_;

	//画像
	Sprite* lifeImage[MAX_LIFE_IMAGE]; //ライフごとの画像番号
	Transform imageTransform_;		   //画像の位置・拡大率

	//テキスト
	Text* pLifeText_;                  //ライフの数表示する用
	XMFLOAT2 textPositiom_;            //テキストのポジション

	//拡大縮小
	XMVECTOR  beforeScale_;		       //補間する前の拡大率保存
	XMVECTOR  targetScale_;            //次の目標とする拡大率

	///////////////////////////////関数//////////////////////////////////

	//初期化
	void LifeManager::Initialize()
	{
		//各ライフの画像ロード
		for (int i = Zero; i < MAX_LIFE_IMAGE; i++) { lifeImage[i] = new Sprite; }
		
		lifeImage[Zero]->Load("Image/Player/PlayerHP0.png");
		lifeImage[One]->Load("Image/Player/PlayerHP1.png");
		lifeImage[Two]->Load("Image/Player/PlayerHP2.png");
		lifeImage[Three]->Load("Image/Player/PlayerHP3.png");

		//テキストの初期化
		ARGUMENT_INITIALIZE(pLifeText_, new Text);
		pLifeText_->Initialize();

		//画像のポジション設定
		ARGUMENT_INITIALIZE(imageTransform_.position_.x, GetPrivateProfilefloat("POSITION", "lifeImageX", "1", "Image/Player/lifePosition.ini"));
		ARGUMENT_INITIALIZE(imageTransform_.position_.y, GetPrivateProfilefloat("POSITION", "lifeImageY", "1", "Image/Player/lifePosition.ini"));
		
		//テキストのポジション設定
		ARGUMENT_INITIALIZE(textPositiom_.x, GetPrivateProfilefloat("POSITION", "lifeTextX", "1", "Image/Player/lifePosition.ini"))
		ARGUMENT_INITIALIZE(textPositiom_.y, GetPrivateProfilefloat("POSITION", "lifeTextY", "1", "Image/Player/lifePosition.ini"))

		//補間する前の拡大率保存
		ARGUMENT_INITIALIZE(beforeScale_, MIN_SCALE);

		//次の目標とする拡大率の保存
		ARGUMENT_INITIALIZE(targetScale_, MAX_SCALE);

		//Playreのライフ初期化
		ARGUMENT_INITIALIZE(playerLife_, NORMAL_PLAYER_LIFE);
	}

	//シーン遷移の時の初期化
	void LifeManager::SceneTransitionInitialize()
	{
		//テキストの初期化
		ARGUMENT_INITIALIZE(pLifeText_, new Text);
		pLifeText_->Initialize();
	}

	//ダメージ食らった時に呼ぶメソッド
	void LifeManager::Damage(int damage)
	{
		//ライフを削る
		playerLife_ -= damage;

		//もし死んでいたらGameManagerに死んだこと伝える
		if(IsDie()){ GameManager::PlayerDie(); }
	}

	//HPUI描画
	void LifeManager::Draw()
	{
		//もしPlayerのライフが2以下なら
		if (playerLife_ <= Two)
			ImageScaling();
		else
		{
			ARGUMENT_INITIALIZE(imageTransform_.scale_, XMFLOAT3(NORMAL_SCALE))
		}

		//画像
		{
			//テクスチャのサイズ取得
			XMFLOAT3 size = lifeImage[playerLife_]->GetTextureSize();

			//切り抜き範囲をリセット（画像全体を表示する）
			RECT rect;
			rect.left = ZERO;
			rect.top = ZERO;
			rect.right = (long)size.x;
			rect.bottom = (long)size.y;

			//描画
			lifeImage[playerLife_]->Draw(imageTransform_, rect);
		}


		//テキスト
		{
			pLifeText_->Draw(textPositiom_.x, textPositiom_.y, playerLife_, imageTransform_.scale_.x);
		}

#pragma region HP操作

		if (Input::IsKeyDown(DIK_A))
		{
			playerLife_--;
		}
		if (Input::IsKeyDown(DIK_D))
		{
			playerLife_++;
		}

#pragma endregion

	}

	//画像の拡大縮小
	void LifeManager::ImageScaling()
	{
		//拡大率を補間しながら変えていくプレイヤーライフが1の時は補間係数を高くする
		if(playerLife_ == One)
			XMStoreFloat3(&imageTransform_.scale_, XMVectorLerp(XMLoadFloat3(&imageTransform_.scale_), targetScale_, ONELIFE_INTERPOLATION_FACTOR));
		else
			XMStoreFloat3(&imageTransform_.scale_, XMVectorLerp(XMLoadFloat3(&imageTransform_.scale_), targetScale_, NORMAL_INTERPOLATION_FACTOR));

		//距離が0.01より短いのなら
		if (RangeCalculation(imageTransform_.scale_, VectorToFloat3(targetScale_)) < CHANGE_TARGET_DISTANCE)
		{
			//ターゲット交換
			std::swap(beforeScale_, targetScale_);
		}
	}

	//死んだどうか
	bool LifeManager::IsDie() { return (playerLife_ <= ZERO); }
}