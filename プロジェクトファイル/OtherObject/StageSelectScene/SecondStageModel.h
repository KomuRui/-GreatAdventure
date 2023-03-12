#pragma once
#include "StageModelBase.h"

/// <summary>
/// ステージを選択する時の２番目のステージ
/// </summary>
class SecondStageModel : public StageModelBase
{
	//回転するモデルの番号
	int hRotationModel_;

	//回転するモデルのトランスフォーム
	Transform tRotation_;

public:

	//コンストラクタ
	SecondStageModel(GameObject* parent, std::string ModelPath, std::string name);

	//初期化
	void ChildInitialize() override;

	//更新
	void ChildUpdate()override;

	//描画
	void ChildDraw()override;

	//選択されている時にボタンを押された時
	void SelectButtonPush() override;

	//指定した時間で呼ばれるメソッド
	void TimeMethod() override;
};

