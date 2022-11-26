#pragma once
#include "../Stage.h"


//ゲームのいろいろな管理をする
namespace GameManager
{
	//ステージのポインタセット
	void SetpStage(Stage* stage);

	//ステージのポインタゲット
	Stage* GetpStage();
};

