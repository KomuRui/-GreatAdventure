#pragma once
#include "../Engine/GameObject.h"

//球
class Bullet : public GameObject
{
	////定数

	const int LIFE_TIME = 180;                   //生存時間
	const XMFLOAT3 COLLIDER_POS = { 0,0,0 };     //コライダーの位置
	const float    COLLIDER_SIZE = 2.0f;         //コライダーのサイズ

	////変数
	
	int hModel_;			//モデル番号
	int lifeTimeCount_;		//どのくらい生存しているか
	float speed_;			//球のスピード
	XMVECTOR front_;		//前ベクトル


public:

	//コンストラクタ
	Bullet(GameObject* parent);

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

	/////////////////////セットゲット関数//////////////////////

	//前ベクトルセットする
	void SetFront(const XMVECTOR& v) { front_ = v; }
};

