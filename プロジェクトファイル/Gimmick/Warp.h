#pragma once
#include "../Mob/Mob.h"
#include "../Player/PlayerBase.h"
#include "../Engine/GameObject/PolyLine.h"
#include "../Manager/SceneManager/SceneManager.h"

/// <summary>
/// ワープの型(他のクラスでも参照したいので外に出す)
/// </summary>
enum WarpType
{
	Normal = 0,
	InverseNormalAndDown,
	MoveToPurpose
};

/// <summary>
/// Playerが次の星に行くために必要なワープクラス
/// </summary>
class Warp : public Mob
{
private:

	//ワープの状態
	enum WarpStatus
	{
		STOP,
		MOVE,
		MAX_WARP_STATUS
	};

	//変数
	float    turnoverRate_;		//回転率
	int      status_;			//状態
	int      type_;		    	//ワープの型
	int      stageReleaseNum_;  //ステージ解放の数(HomeSceneに戻るときに使うため)  
	XMFLOAT3 playerPos_;        //ワープにPlayerを乗せるときのPlayerのポジションを設定
	PolyLine* pRightLine_;      //ワープのエフェクト右側
	PolyLine* pLeftLine_;       //ワープのエフェクト左側
	PolyLine* pBaseLine_;       //ワープのエフェクト右側
	XMFLOAT3 warpTarget_;	    //ワープの移動先
	SCENE_ID id_;				//シーン遷移のID

public:

	//コンストラクタ
	Warp(GameObject* parent, std::string modelPath, std::string name);

	//デストラクタ
	~Warp();

	//初期化
	void ChildInitialize() override;

	//スタートアップデート
	void ChildStartUpdate() override;

	//ワープの動き方
	void ChildUpdate() override;

	//継承先用の描画
	void ChildDraw() override;

	//継承先用の開放
	void ChildRelease() override;

	/// <summary>
	/// 次の星まで移動
	/// </summary>
	void MovingToStar();

	/// <summary>
	/// 次の目的地まで移動
	/// </summary>
	void MovingToPurpose();

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="pTarget">当たった相手のポインタ</param>
	void OnCollision(GameObject* pTarget) override;

	/// <summary>
	/// ワープの型セット
	/// </summary>
	/// <param name="num">セットしたい型</param>
	void SetWarpType(const int& type) { type_ = type; }

	/// <summary>
	/// ワープの移動先設定
	/// </summary>
	/// <param name="target"></param>
	void SetWarpTarget(const XMFLOAT3& target) { warpTarget_ = target; }

	/// <summary>
	/// 法線をセット
	/// </summary>
	/// <param name="nor">セットしたい法線</param>
	void SetNormal(const XMVECTOR& nor) { vNormal_ = nor; }

	/// <summary>
	/// シーンの遷移先IDをセット
	/// </summary>
	/// <param name="id">セットしたいシーンの遷移先ID</param>
	void SetSceneId(const SCENE_ID& id) { id_ = id; }

	/// <summary>
	/// 解放ステージをセット
	/// </summary>
	void SetStageRelease(const int& num) { stageReleaseNum_ = num; }
};

