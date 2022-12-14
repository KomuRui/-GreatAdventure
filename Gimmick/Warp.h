#pragma once
#include "../Mob.h"
#include "../Player.h"
#include "../Engine/PolyLine.h"
#include "../Engine/SceneManager.h"

//ワープクラス
class Warp : public Mob
{
private:

	//ワープに状態
	enum WarpStatus
	{
		STOP,
		MOVE,
		MAX_WARP_STATUS
	};

	//ポリラインを出すときの
	enum PolyLineNumber
	{
		RIGHT,
		LEFT,
		BASE,
		MAX_POLY_LINE
	};

	//定数
	const int      FADE_OUT_DISTANCE = 600;          //フェードアウトする時の距離
	const int      SCENE_MOVE_DISTANCE = 300;        //シーン移行する時の距離
	const float    ROTATION_QUANTITY = 0.02f;        //回転量
	const float    ADDITION_TURNOVERRATE = 0.03f;    //回転率を加算する量
	const float    MAX_TURNOVERRATE = 10.0f;         //最大回転率
	const XMFLOAT3 COLLIDER_POS = { 0, -2, 0 };      //コライダーポジション
	const XMFLOAT3 COLLIDER_SIZE = { 5.5, 4, 5.5 };  //コライダーサイズ

	//変数
	float    turnoverRate_;			 //回転率
	int      status_;				 //状態
	int      number_;				 //ワープの番号
	XMFLOAT3 playerPos_;			 //ワープにPlayerを乗せるときのPlayerのポジションを設定
	PolyLine* pLine[MAX_POLY_LINE];  //ワープのエフェクト
	XMFLOAT3 warpTarget_;			 //ワープの移動先
	SCENE_ID id_;					 //シーン遷移のID

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

	//次の星まで移動
	void MovingToStar();

	//次の目的地まで移動
	void MovingToPurpose();

	//当たり判定
	void OnCollision(GameObject* pTarget) override;

	//ワープの番号セット
	void SetNumber(const int& num) { number_ = num; }

	//ワープの移動先設定
	void SetWarpTarget(const XMFLOAT3& target) { warpTarget_ = target; }

	//法線をセット
	void SetNormal(const XMVECTOR& nor) { vNormal = nor; }

	//シーン遷移先のIDをセット
	void SetSceneId(const SCENE_ID& id) { id_ = id; }
};

