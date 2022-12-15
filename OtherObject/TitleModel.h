#pragma once
#include "../Engine/GameObject.h"

//タイトルのモデル
class TitleModel : public GameObject
{
	//モデル番号
	int hModel_;

public:

	//コンストラクタ
	TitleModel(GameObject* parent);

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

