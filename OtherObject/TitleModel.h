#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Particle.h"

//タイトルのモデル
class TitleModel : public GameObject
{
	////定数

	const XMVECTOR MIN_SCALE = { 0.2,0.2,1.0 };    //最低拡大率
	const XMVECTOR MAX_SCALE = { 0.25,0.25,1.0 };  //最高拡大率
	const float INTERPOLATION_FACTOR = 0.03f;      //補間係数
	const float CHANGE_TARGET_DISTANCE = 0.01f;    //ターゲット変更するときの距離

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

	//シーン変更エフェクト
	void SceneChangeEffect();
};

