#pragma once
#include "GameObject.h"
#include "../ResourceManager/CreateStage.h"

//各ステージで場所ごとにカメラ遷移するために必要なオブジェクト
class CameraTransitionObject : public GameObject
{
private:

	//必要な情報
	StageCameraTransition info_;

	//誰かと当たっているか
	bool isHit_;

	//カメラ動かすかどうか
	bool isCameraMove_;

public:

	//コンストラクタ
	CameraTransitionObject(GameObject* parent, const StageCameraTransition& camInfo);

	/////////////////////オーバーライドする関数//////////////////////

    //初期化
	void Initialize() override;

	//更新の前に一回呼ばれる関数
	void StartUpdate() override {};

	//更新
	void Update() override {};

	//描画
	void Draw() override {};

	//開放
	void Release() override {};

	//当たり判定(なにかと当たった時)
	void OnCollision(GameObject* pTarget) override;

	//当たり判定(誰とも当たっていない時)
	void OutCollision() override;

	//指定した時間で呼ばれるメソッド
	void TimeMethod() override;

	/// <summary>
	/// カメラを動かすかどうかセット
	/// </summary>
	/// <param name="flag">trueなら動かす,falseなら動かさない</param>
	void SetCamMoveFlag(const bool& flag) { isCameraMove_ = flag; }
};

