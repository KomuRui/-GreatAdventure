#pragma once
#include "../Mob.h"
#include "../Player.h"
#include "../Engine/PolyLine.h"
#include "../Engine/SceneManager.h"

//動く床クラス
class MoveFloor : public Mob
{
private:

	//変数
	int      status_;          //状態
	int      number_;          //ワープの番号
	XMFLOAT3 MoveFloorTarget_; //ワープの移動先

	//状態
	enum Status
	{
		STOP,
		MOVE,
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

	//次の目的地まで移動
	void MovingToPurpose();

	//ワープの番号セット
	void SetNumber(const int& num) { number_ = num; }

	//ワープの移動先設定
	void SetMoveFloorTarget(const XMFLOAT3& target) { MoveFloorTarget_ = target; }

};

