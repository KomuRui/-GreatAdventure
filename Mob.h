#pragma once
#include "Engine/GameObject.h"
#include "Engine/BoxCollider.h"
#include "Engine//SphereCollider.h"
#include "Engine/Global.h"
#include "Stage.h"
#include "Engine/Particle.h"

//■■シーンを管理するクラス
class Mob : public GameObject
{
protected:

	///////////////キャラの必要な情報///////////////////
	 
	XMMATRIX TotalMx;			     //キャラの横軸のいままでのマトリクスの総括マトリクス

	XMVECTOR Up;                     //キャラの上ベクトル
	XMVECTOR Down;		   	         //キャラの下ベクトル
	XMVECTOR vNormal;                //キャラの下のステージの法線

	float Angle;                     //キャラの上の軸の角度

	int hModel_;                     //モデル番号
	std::string ModelNamePath_;      //ファイルネームパス

	///////////////当たり判定///////////////////

	Stage* pstage_;                 //ステージクラスのポインタ
	int      hGroundModel_;         //ステージのモデル番号を入れる変数

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Mob(GameObject* parent,std::string modelPath, std::string name);

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

	//ステージに合わせてMobを回転
	void RotationInStage();

	//継承先ごとにUpdateでの動き方を変える
	virtual void ChildUpdate() {};

	//継承先用の初期化
	virtual void ChildInitialize() {};

	//継承先用の描画
	virtual void ChildDraw() {};

	//継承先用のスタートアップデート
	virtual void ChildStartUpdate() {};

	//継承先用の開放
	virtual void ChildRelease() {};

	//継承先用のコライダー当たった時に呼ばれる関数
	virtual void OnCollision(GameObject* pTarget) override {};

	//継承先用の指定した時間で呼ばれるメソッド
	virtual void TimeMethod() override {};
};

