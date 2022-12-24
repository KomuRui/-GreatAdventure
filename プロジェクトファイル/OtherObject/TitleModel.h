#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Particle.h"

//タイトルのモデル
class TitleModel : public GameObject
{
	////変数

	XMVECTOR  beforeScale_;		  //補間する前の拡大率保存
	XMVECTOR  targetScale_;       //次の目標とする拡大率
	Particle* pSceneChabgeEffect_;//シーン変更エフェクト
	int hModel_;   				  //モデル番号

public:

	//コンストラクタ
	TitleModel(GameObject* parent);

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

	////////////////////////////関数///////////////////////////////

	/// <summary>
	/// シーン変更エフェクト
	/// </summary>
	void SceneChangeEffect();
};

