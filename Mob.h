#pragma once
#include "Engine/GameObject.h"
#include "Engine/BoxCollider.h"
#include "Engine//SphereCollider.h"
#include "Engine/Global.h"

//■■シーンを管理するクラス
class Mob : public GameObject
{
protected:

	//モデル番号
	int hModel_;

	//ファイルネームパス
	std::string ModelNamePath_;

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

	//継承先ごとにUpdateでの動き方を変える
	virtual void UpdateMove() {};

	//継承先用の初期化
	virtual void ChildInitialize() {};

	//継承先用の描画
	virtual void ChildDraw() {};

	//継承先用のスタートアップデート
	virtual void ChildStartUpdate() {};

	//継承先用のコライダー当たった時に呼ばれる関数
	virtual void OnCollision(GameObject* pTarget) override { int a = 0; }

};

