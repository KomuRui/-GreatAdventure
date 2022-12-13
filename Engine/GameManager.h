#pragma once
#include "../Stage.h"
#include "../Player.h"

//ゲームのいろいろな管理をする
namespace GameManager
{
	//プレイヤーのポインタセット
	void SetpPlayer(Player* player);

	//プレイヤーのポインタゲット
	Player* GetpPlayer();

	//ステージのポインタセット
	void SetpStage(Stage* stage);

	//ステージのポインタゲット
	Stage* GetpStage();

	//フェード描画
	void FadeDraw();

	//フェードイン描画
	void FadeInDraw();

	//フェードアウト描画
	void FadeOutDraw();
};

