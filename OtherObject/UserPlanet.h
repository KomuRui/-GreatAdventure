#pragma once
#include "../Engine/GameObject.h"

//タイトルのPlayerモデル
class UserPlanet : public GameObject
{
	////定数

	const float RATATION_SPEED = 0.1f;    //回転速度

	////変数

	std::string ModelNamePath_; //ファイルネームパス
	int hModel_; 				//モデル番号格納用

public:

	//コンストラクタ
	UserPlanet(GameObject* parent, std::string modelPath, std::string name);

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

