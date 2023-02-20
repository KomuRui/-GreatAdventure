#pragma once
#include "../../Stage.h"
#include "../../Player/PlayerBase.h"
#include "../../Engine/SceneManager.h"

class Warp;

//フェードの状態の列挙型
enum FadeStatus
{
	NOOP,     //何もしない
	DRAW,     //画像だけ表示
	FADE_IN,  //フェードイン
	FADE_OUT, //フェードアウト
	GAME_OVER //ゲームオーバー 
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

	///////////////////////////////フェード用関数////////////////////////////////////
	
	/// <summary>
	/// 普通の画像を表示
	/// </summary>
	void NormalDraw();

	/// <summary>
	/// 状態によって呼ぶ関数分ける
	/// </summary>
	void FadeDraw();

	/// <summary>
	/// フェードイン描画
	/// </summary>
	void FadeInDraw();

	/// <summary>
	/// フェードアウト描画
	/// </summary>
	void FadeOutDraw();

	/// <summary>
	/// ゲームオーバー描画
	/// </summary>
	void GameOverDraw();

	/// <summary>
	/// 状態をセット
	/// </summary>
	/// <param name="status">セットしたい状態</param>
	 
	/// <summary>
	/// 状態をセット
	/// </summary>
	/// <param name="status">セットしたい状態</param>
	/// <param name="filename"></param>
	void SetStatus(int status, std::string filename = "");

	/// <summary>
	/// 現在の状態を取得
	/// </summary>
	/// <returns>現在の状態</returns>
	int GetStatus();
};

