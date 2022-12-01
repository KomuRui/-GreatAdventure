#pragma once
#include "../../../Stage.h"

//ステージクラス
class WorldStage1 : public Stage
{
	//ステージ用のモデル
	enum StageModel
	{
		Rotation,
		STAGE_MODEL_MAX
	};

	//モデル番号格納用
	int Model_[STAGE_MODEL_MAX];

	//回転するオブジェクト用のトランスフォーム
	Transform tRotation_;  

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	WorldStage1(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新の前に一回呼ばれる関数
	void StartUpdate() override {};

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

