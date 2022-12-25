#pragma once
#include "../Mob.h"
#include "../Player.h"
#include "../Engine/PolyLine.h"
#include "../Engine/SceneManager.h"

/// <summary>
/// 動く床クラス
/// </summary>
class MoveFloor : public Mob
{
private:

	//変数
	int      status_;          //状態
	XMFLOAT3 MoveFloorTarget_; //ワープの移動先

	//状態
	enum Status
	{
		STOP,      //停止状態
		MOVE,      //動く状態
		MAX_STATUS
	};

public:

	//コンストラクタ
	MoveFloor(GameObject* parent, std::string modelPath, std::string name);

	//デストラクタ
	~MoveFloor();

	//スタートアップデート
	void ChildStartUpdate() override;

	//ワープの動き方
	void ChildUpdate() override;

	/// <summary>
	/// 次の目的地まで移動
	/// </summary>
	void MovingToPurpose();

	/// <summary>
	/// ワープの移動先設定
	/// </summary>
	/// <param name="target">設定したいワープの移動先</param>
	void SetMoveFloorTarget(const XMFLOAT3& target) { MoveFloorTarget_ = target; }

	/// <summary>
	/// 動くようにセット
	/// </summary>
	void SetMove() {  status_ = MOVE; }

};

