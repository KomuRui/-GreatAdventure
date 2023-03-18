#pragma once
#include "../../Stage.h"
#include "../../Player/PlayerBase.h"
#include "../../Manager/SceneManager/SceneManager.h"

class Warp;

//ゲームのいろいろな管理をする
namespace GameManager
{
	///////////////////////////////関数//////////////////////////////////
	
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// シーン遷移の時の初期化
	/// </summary>
	void SceneTransitionInitialize();

	/// <summary>
	/// Playerが死亡した時にLifeManagerから呼ばれる
	/// </summary>
	void PlayerDie();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画(コインの取得数やPlayerライフの表示)
	/// </summary>
	void Draw();

	/// <summary>
	/// ポーズ画面を削除
	/// </summary>
	void PauseDelete();

	///////////////////////////////セットゲット関数//////////////////////////////////

	//プレイヤーのポインタセット
	void SetpPlayer(PlayerBase* player);

	//プレイヤーのポインタゲット
	PlayerBase* GetpPlayer();

	//ステージのポインタセット
	void SetpStage(Stage* stage);

	//ステージのポインタゲット
	Stage* GetpStage();

	//ワープのポインタセット
	void SetpWarp(Warp* warp);

	//ワープのポインタゲット
	Warp* GetpWarp();

	//シーンマネージャーのポインタセット
	void SetpSceneManager(SceneManager* scene);

	//シーンマネージャーのポインタゲット
	SceneManager* GetpSceneManager();
};

