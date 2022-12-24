#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/CreateStage.h"

//タイトルのモデル
class TitleComplexModel : public GameObject
{
	////変数

	int hModel_;  				//モデル番号
	CreateStage* pCreateStage;  //ステージを作成するために必要

public:

	//コンストラクタ
	TitleComplexModel(GameObject* parent);

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
};

