#pragma once
#include "Engine/GameObject.h"
#include <vector>

//前方宣言
class Block;

//各ステージクラスのもととなるクラス
class Stage : public GameObject
{
protected:

	/////////////////////////Stageに必要な情報/////////////////////////////////
	
	//モデルの種類
	enum StageCategory
	{
		Base = 0,      //ステージのモデル
		Space,		   //背景の宇宙モデル
		PolyModel,     //球体に物体を乗せるために疑似モデル
		MAX
	};

	////2Dの際のブロックとの当たり判定に使う
	enum BlockHitTest2D
	{
		Right = 0,     //右
		Left,          //左
		Under,         //下
		Top,           //上
	};

	//モデル番号
	int hModel_[MAX];

	//背景モデル用のトランスフォーム
	Transform tSpace_;

	//画角
	int fieldAngle_;

	//ライトの強さ
	int lightIntensity_;

	/////////////////////////他のクラスで必要な情報/////////////////////////////////

	//Playerの初期位置
	XMFLOAT3 pos_;

	//ワープの移動先
	XMFLOAT3 warpPos_;

	//3Dのモデルを使用しているかどうか
	bool threeDflag_;

	//球体モデルを使用しているかどうか
	bool circleFlag_;

	//ブロックを保存しておくVector(後にブロックとの当たり判定を行うために使う)
	std::vector<Block*> tBlock_;

public:

	//コンストラクタ
	Stage(GameObject* parent,std::string name);

	/////////////////////オーバーライドする関数//////////////////////

	//初期化
	virtual void Initialize() override {};

	//更新の前に一回呼ばれる関数
	virtual void StartUpdate() override {};

	//更新
	virtual void Update() override {};

	//描画
	virtual void Draw() override {};

	//開放
	virtual void Release() override {};

	//////////////////////////////関数////////////////////////////////////
	
	//そこにブロックがあるかどうか,もしあったら重なっている分ずらす
	//引数:status 0:右 1:左 2:上 3:下 
	bool IsBlock(XMFLOAT3* pos, int status);

	////////////////////////ゲット・セット関数///////////////////////////

	//モデル番号のゲット関数
	int GethModel() { return hModel_[Base]; }

	//球体に物体を乗せるために疑似モデル番号のゲット関数
	int GetPolyModell() { return hModel_[PolyModel]; }

	//Posのゲット関数
	XMFLOAT3 GetPos() { return pos_; }

	//ワープの移動先取得
	XMFLOAT3 GetWarpTargetPos() { return warpPos_; }

	//3Dの動きをさせたいか
	bool GetthreeDflag() { return threeDflag_; }

	//球体上で動きをさせたいか
	bool GetCircleflag() { return circleFlag_; }
};

