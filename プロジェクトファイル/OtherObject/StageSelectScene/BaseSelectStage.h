#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/Component/EasingMove.h"
#include "StageModelBase.h"
#include <map>

//各チェックポイントの番号
enum class CheckPoint
{
	FIRST = 1,
	NONE,
	SECOND,
	NONE2,
	THIRD,
	NONE3,
	FOURTH,
	NONE4,
};

/// <summary>
/// ステージを選択する時のベースとなるクラス
/// </summary>
class BaseSelectStage : public GameObject
{
	//モデル番号
	int hModel_;

	//イージングに必要な変数
	EasingMove* pEasing_;

	//どのチェックポイントを見ているか
	int lookCheckPoint_;

	//チェックポイントに該当するStageModelを格納する場所
	std::map<int, StageModelBase*> table_;

public:

	//コンストラクタ
	BaseSelectStage(GameObject* parent);

	////////////////////////オーバーライドする関数//////////////////////////////

	//初期化
	void Initialize() override;

	//更新の前に一回呼ばれる関数
	void StartUpdate() override {};

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override {};

	////////////////////////関数//////////////////////////////

	/// <summary>
	/// チェックポイント計算
	/// </summary>
	/// <param name="sige">プラス方向かマイナス方向か</param>
	void CheckPointCalc(int sige);

	/// <summary>
	/// チェックポイントモデルをセット
	/// </summary>
	/// <param name="checkPointNum">何番目のチェックポイントか</param>
	/// <param name="p">セットしたいStageModel</param>
	void SetCheckPointModel(int checkPointNum, StageModelBase* p) { table_[checkPointNum] = p; }
};

