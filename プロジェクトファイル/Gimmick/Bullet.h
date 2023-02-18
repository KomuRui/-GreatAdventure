#pragma once
#include "../Engine/GameObject.h"

//球
class Bullet : public GameObject
{

	int hModel_;			//モデル番号
	int lifeTimeCount_;		//どのくらい生存しているか
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

	//コライダーに当たった時に呼ばれる関数
	void OnCollision(GameObject* pTarget) override;

	////////////////////////////関数/////////////////////////////

	//ノックバック
	void KnockBack();

	/////////////////////セットゲット関数//////////////////////

	/// <summary>
	/// 前ベクトルをセット
	/// </summary>
	/// <param name="v">セットしたい前ベクトル</param>
	void SetFront(const XMVECTOR& v) { front_ = v; }
};

