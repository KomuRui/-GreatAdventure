#pragma once
#include "StageModelBase.h"

/// <summary>
/// ステージを選択する時の２番目のステージ
/// </summary>
class SecondStageModel : public StageModelBase
{

public:

	//コンストラクタ
	SecondStageModel(GameObject* parent, std::string ModelPath, std::string name);

};

