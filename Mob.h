#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fade.h"
#include "Button.h"

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
	Mob(GameObject* parent,std::string modelPath);

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
	virtual void UpdateMove();

};

//コインクラス
class Coin : public Mob
{
public:

	//コンストラクタ
	Coin(GameObject* parent, std::string modelPath) :Mob(parent, modelPath) {}

	//コインの動き方
	void UpdateMove() override;
};

