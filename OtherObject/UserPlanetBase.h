#pragma once
#include "../Engine/GameObject.h"

//ユーザーの星のベースクラス
class UserPlanetBase : public GameObject
{
	//状態
	enum Status
	{
		Stop,
		Move,
		MAX_STATUS
	};

	////定数

	const float RATATION_SPEED = 0.1f;    //回転速度

	////変数

	int hModel_; 				//モデル番号格納用
	int status_;                //状態
	std::string ModelNamePath_; //ファイルネームパス
	XMFLOAT3 nextPos_;          //次のポジション

public:

	//コンストラクタ
	UserPlanetBase(GameObject* parent, std::string modelPath, std::string name);

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

	/////////////////////継承先用の関数//////////////////////

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

	/////////////////////関数//////////////////////

	//次の位置へ移動
	void NextPositionToMove();

	//次のポジションセット
	void SetNextPosition(const XMFLOAT3& nextPos) { nextPos_ = nextPos; }
};

