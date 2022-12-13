#pragma once
#include "../Stage.h"
#include "../Player.h"

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
	
	//初期化
	void Initialize();

	///////////////////////////////セットゲット関数//////////////////////////////////
	
	//プレイヤーのポインタセット
	void SetpPlayer(Player* player);

	//プレイヤーのポインタゲット
	Player* GetpPlayer();

	//ステージのポインタセット
	void SetpStage(Stage* stage);

	//ステージのポインタゲット
	Stage* GetpStage();

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
};

