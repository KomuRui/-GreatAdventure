#pragma once
#include "../Engine/GameObject/GameObject.h"

//水流を発生する棒
class WaterCurrentStick : public GameObject
{
	int hModel_;   			//モデル番号
	int hEffect_;           //エフェクト番号
	std::string filePath_;  //ファイルのパス

	XMVECTOR front_;        //前ベクトル

public:

	//コンストラクタ
	WaterCurrentStick(GameObject* parent, std::string modelFilePath_, std::string name);

	/////////////////////オーバーライドする関数//////////////////////

	//初期化
	void Initialize() override;

	//更新の前に一回呼ばれる関数
	void StartUpdate() override {};

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

