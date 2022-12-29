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

	/// <summary>
	/// 描画(コインの取得数やPlayerライフの表示)
	/// </summary>
	void Draw();

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
	/// 状態をセット
	/// </summary>
	/// <param name="status">セットしたい状態</param>
	void SetStatus(int status);

	/// <summary>
	/// 現在の状態を取得
	/// </summary>
	/// <returns>現在の状態</returns>
	int GetStatus();
};

