#pragma once
#include "GameObject.h"
#include "ImGuiSet.h"

//各ステージで場所ごとにカメラ遷移するために必要なオブジェクト
class CameraTransitionObject : public GameObject
{
private:

	StageCameraTransition info;

public:

	//コンストラクタ
	CameraTransitionObject(GameObject* parent, const StageCameraTransition& camInfo);

	/////////////////////オーバーライドする関数//////////////////////

    //初期化
	void Initialize() override;

	//更新の前に一回呼ばれる関数
	void StartUpdate() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//当たり判定
	void OnCollision(GameObject* pTarget) override;
};

