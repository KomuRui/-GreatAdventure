#pragma once
#include "../Engine/GameObject.h"

//球
class Bullet : public GameObject
{
	////定数

	//生存時間
	const int LIFE_TIME = 180;

	////変数
	
	//モデル番号
	int hModel_;

	//どのくらい生存しているか
	int lifeTimeCount_;

	//球のスピード
	float speed_;

	//前ベクトル
	XMVECTOR front_;


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

