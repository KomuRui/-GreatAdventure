#pragma once
#include "StageModelBase.h"

/// <summary>
/// ステージを選択する時の１番目のステージ
/// </summary>
class FirstStageModel : public StageModelBase
{

public:

	//コンストラクタ
	FirstStageModel(GameObject* parent,std::string ModelPath,std::string name);

	//初期化
	void ChildInitialize() override;

	//更新
	void ChildUpdate()override;

	//選択されている時にボタンを押された時
	void SelectButtonPush() override;

	//指定した時間で呼ばれるメソッド
	void TimeMethod() override;
};

