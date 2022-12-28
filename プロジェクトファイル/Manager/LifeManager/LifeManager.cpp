#include "LifeManager.h"
#include "../../Engine/Global.h"
#include "../GameManager/GameManager.h"

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
	///////////////////////////////変数//////////////////////////////////

	//Playerの現在のライフの総数
	int playerLife;

	///////////////////////////////関数//////////////////////////////////

	//初期化
	void LifeManager::Initialize()
	{
		ARGUMENT_INITIALIZE(playerLife, NORMAL_PLAYER_LIFE);
	}

	//ダメージ食らった時に呼ぶメソッド
	void LifeManager::Damage(int damage)
	{
		//ライフを削る
		playerLife -= damage;

		//もし死んでいたらGameManagerに死んだこと伝える
		if(IsDie()){ GameManager::PlayerDie(); }
	}

	//死んだどうか
	bool LifeManager::IsDie() { return (playerLife <= ZERO); }
}