#include "LifeManager.h"
#include "../../Engine/Global.h"
#include "../GameManager/GameManager.h"
#include "../../Engine/Image.h"

//定数
namespace
{
	static const int NORMAL_PLAYER_LIFE = 3; //普通のPlayerのライフの数
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

	//ライフごとの画像番号
	int lifeImage[MAX_LIFE_IMAGE];

	///////////////////////////////関数//////////////////////////////////

	//初期化
	void LifeManager::Initialize()
	{
		//各ライフの画像ロード
		lifeImage[Zero] = Image::Load("Image/Player/PlayerHP0.png");
		lifeImage[One] = Image::Load("Image/Player/PlayerHP1.png");
		lifeImage[Two] = Image::Load("Image/Player/PlayerHP2.png");
		lifeImage[Three] = Image::Load("Image/Player/PlayerHP3.png");
		

		//Playreのライフ初期化
		ARGUMENT_INITIALIZE(playerLife_, NORMAL_PLAYER_LIFE);
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

	}

	//死んだどうか
	bool LifeManager::IsDie() { return (playerLife_ <= ZERO); }
}