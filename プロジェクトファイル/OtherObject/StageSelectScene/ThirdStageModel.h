#pragma once
#include "StageModelBase.h"


/// <summary>
/// ステージを選択する時の3番目のステージ
/// </summary>
class ThirdStageModel : public StageModelBase
{

public:

	//コンストラクタ
	ThirdStageModel(GameObject* parent, std::string ModelPath, std::string name);

	//初期化
    void ChildInitialize()override;

	//更新
	void ChildUpdate()override;
};

