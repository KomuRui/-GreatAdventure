#pragma once
#include "../Engine/GameObject/GameObject.h"

/// <summary>
/// ボスが倒されたシーン用
/// </summary>
class BossEnemyKill : public GameObject
{

	int hModel_;	  //モデル番号
	int hImage_;      //画像番号
	int sign_;        //符号

	float colorR_;    //RGB値のRの値
	float imageAlpha_;//画像の透明度

	bool isExplosion_;//爆発したか
	bool isFadeIn_;   //フェードインするか
	bool isModelDraw_;//モデル描画するか 

	XMFLOAT3 camTar_; //カメラのターゲット

public:

	//コンストラクタ
	BossEnemyKill(GameObject* parent);

	/////////////////////オーバーライドする関数///////////////////////////

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

	//指定した時間で呼ばれるメソッド
	void TimeMethod() override;
};

