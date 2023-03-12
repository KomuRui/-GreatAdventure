#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/Component/EasingMove.h"


/// <summary>
/// ステージを選択する時のベースとなるクラス
/// </summary>
class BaseSelectStage : public GameObject
{
	//モデル番号
	int hModel_;

	//イージングに必要な変数
	EasingMove* pEasing_;

public:

	//コンストラクタ
	BaseSelectStage(GameObject* parent);

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
};

