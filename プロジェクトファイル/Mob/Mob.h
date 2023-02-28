#pragma once
#include "../Engine/GameObject/GameObject.h"
#include "../Engine/Collider/BoxCollider.h"
#include "../Engine/Collider/SphereCollider.h"
#include "../Engine/ResourceManager/Global.h"
#include "../Stage.h"
#include "../Engine/ResourceManager/Model.h"

/// <summary>
/// 地形に合わせて回転させたいオブジェクトの基底クラス(Mob,Enemy,Warp,Coinなど...)
/// </summary>
class Mob : public GameObject
{
protected:

	///////////////キャラの必要な情報///////////////////
	 
	XMMATRIX totalMx_;			     //キャラの横軸のいままでのマトリクスの総括マトリクス

	XMVECTOR up_;                    //キャラの上ベクトル
	XMVECTOR horizontal_;            //キャラの横
	XMVECTOR down_;		   	         //キャラの下ベクトル
	XMVECTOR vNormal_;               //キャラの下のステージの法線

	float angle_;                    //キャラの上の軸の角度

	int hModel_;                     //モデル番号
	std::string modelNamePath_;      //ファイルネームパス

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
	virtual void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//更新の前に一回呼ばれる関数
	void StartUpdate() override;

	/// <summary>
	/// ステージに合わせて回転
	/// </summary>
	virtual void RotationInStage();

	/// <summary>
	/// 自身の法線をセット
	/// </summary>
	/// <param name="nor">セットしたい法線</param>
	void SetNormal(const XMVECTOR& nor) { vNormal_ = nor; }

	/// <summary>
	/// キャラの上軸をセット
	/// </summary>
	/// <param name="angle">セットしたいキャラの上軸</param>
	void SetAngle(const float& angle) { angle_ = angle; }

	/// <summary>
	/// Playerを真逆の状態に設定(まったく反対に設定すると外積が０になってしまうので少しずらす)
	/// </summary>
	void SetInverseNormalAndDown() { vNormal_ += {0, 0.1f, 0, 0}; vNormal_ = -vNormal_; down_ = -vNormal_; }

	/// <summary>
	/// モデルパスネームを取得
	/// </summary>
	/// <returns>モデルパスネーム</returns>
	std::string GetModelPathName() { return modelNamePath_; }

	/// <summary>
	/// キャラの下のステージの法線をゲット
	/// </summary>
	/// <returns>ステージの法線</returns>
	XMVECTOR GetNormal() { return vNormal_; }

	/// <summary>
	/// キャラの上軸の角度をゲット
	/// </summary>
	/// <returns>キャラの上軸の角度</returns>
	float GetAngle() { return angle_; }

	/// <summary>
	/// キャラの上軸ゲット
	/// </summary>
	/// <returns>キャラの上軸</returns>
	XMVECTOR GetUp() { return up_; }

	/// <summary>
	/// Playerの下ベクトルゲット
	/// </summary>
	/// <returns>Playerの下ベクトル</returns>
	XMVECTOR GetDown() { return down_; }

	/// <summary>
	/// Playerの回転マトリクスゲット
	/// </summary>
	/// <returns>Playerの回転マトリクス</returns>
	XMMATRIX GetmmRotate() { return transform_.mmRotate_; }

	/// <summary>
	/// モデル番号をゲット
	/// </summary>
	/// <returns>Playerのモデル番号</returns>
	int GethModel() { return hModel_; }

	/// <summary>
	/// アニメーションするかどうかセット
	/// </summary>
	/// <param name="flag">trueならアニメーションする,falseならアニメーションしない</param>
	void SetAnimFlag(const bool& flag) { Model::SetAnimFlag(hModel_, flag); }

	/// <summary>
	/// 継承先用のUpdate
	/// </summary>
	virtual void ChildUpdate() {};

	/// <summary>
	/// 継承先用の初期化
	/// </summary>
	virtual void ChildInitialize() {};

	/// <summary>
	/// 継承先用の描画
	/// </summary>
	virtual void ChildDraw() {};

	/// <summary>
	/// 継承先用の更新の前に一度だけ呼ばれる関数
	/// </summary>
	virtual void ChildStartUpdate() {};

	/// <summary>
	/// 継承先用の開放
	/// </summary>
	virtual void ChildRelease() {};

	/// <summary>
	/// 継承先用のコライダーに当たった時に呼ばれる関数
	/// </summary>
	/// <param name="pTarget">当たったオブジェクトのポインタ</param>
	virtual void OnCollision(GameObject* pTarget) override {};

	/// <summary>
	/// 継承先用の指定した時間で呼ばれるメソッド
	/// </summary>
	virtual void TimeMethod() override {};
};

