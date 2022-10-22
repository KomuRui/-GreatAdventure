#pragma once
#include "../Engine/GameObject.h"

//■■シーンを管理するクラス
class TutorialStage : public GameObject
{
	//ステージ種類の数
	enum StageCategory
	{
		first,
		Two,
		MAX
	};

	//モデル番号
	int hModel_[MAX];

	//ステージごとのPlayerの初期位置
	XMFLOAT3 pos_[MAX];

	//現在どこのステージを表示してるかのステータス
	int status_;

	//3Dのモデルを使用しているかどうか
	bool threeDflag_[MAX];

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TutorialStage(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//更新の前に一回呼ばれる関数
	void StartUpdate() override;

	//モデル番号のゲット関数
	int GethModel() { return hModel_[status_]; }

	//Posのゲット関数
	XMFLOAT3 GetPos() { return pos_[status_]; }

	//3Dの動きをさせたいか
	bool GetthreeDflag() { return threeDflag_[status_]; }
};

