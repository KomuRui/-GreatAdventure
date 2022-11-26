#pragma once
#include "../Mob.h"
#include "../Player.h"
#include "../Engine/PolyLine.h"

//ワープクラス
class Warp : public Mob
{
private:

	//定数
	const float    ROTATION_QUANTITY = 0.02f;        //回転量
	const float    ADDITION_TURNOVERRATE = 0.03f;    //回転率を加算する量
	const float    MAX_TURNOVERRATE = 10.0f;         //最大回転率
	const XMFLOAT3 COLLIDER_POS = { 0, -2, 0 };      //コライダーポジション
	const XMFLOAT3 COLLIDER_SIZE = { 5.5, 4, 5.5 };  //コライダーサイズ

	//変数
	float    turnoverRate_;  //回転率
	int      status_;        //状態
	int      number_;        //ワープの番号
	XMFLOAT3 playerPos_;     //ワープにPlayerを乗せるときのPlayerのポジションを設定
	PolyLine* pLine[3];
	XMFLOAT3 warpTarget;

	//ワープに状態
	enum Status
	{
		STOP,
		MOVE,
		MAX_STATUS
	};

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
	void SetNumber(int num) { number_ = num; }

	//ワープの移動先設定
	void SetWarpTarget(XMFLOAT3 target) { warpTarget = target; }
};

