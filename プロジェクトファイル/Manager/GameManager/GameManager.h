#pragma once
#include "../../Stage.h"
#include "../../Player.h"
#include "../../Engine/SceneManager.h"

//フェードの状態の列挙型
enum FadeStatus
{
	NOOP,     //何もしない
	DRAW,     //画像だけ表示
	FADE_IN,  //フェードイン
	FADE_OUT  //フェードアウト
};

//ゲームのいろいろな管理をする
namespace GameManager
{
	///////////////////////////////関数//////////////////////////////////
	
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// Playerが死亡した時にLifeManagerから呼ばれる
	/// </summary>
	void PlayerDie();

	///////////////////////////////セットゲット関数//////////////////////////////////
	
	//プレイヤーのポインタセット
	void SetpPlayer(Player* player);

	//プレイヤーのポインタゲット
	Player* GetpPlayer();

	//ステージのポインタセット
	void SetpStage(Stage* stage);

	//ステージのポインタゲット
	Stage* GetpStage();

	//シーンマネージャーのポインタセット
	void SetpSceneManager(SceneManager* scene);

	//シーンマネージャーのポインタゲット
	SceneManager* GetpSceneManager();

	///////////////////////////////フェード用関数////////////////////////////////////
	
	//描画
	void Draw();

	//フェード描画
	void FadeDraw();

	//フェードイン描画
	void FadeInDraw();

	//フェードアウト描画
	void FadeOutDraw();

	//状態セット
	void SetStatus(int status);

	//状態ゲット
	int GetStatus();
};

