#pragma once
#include "../Engine/GameObject.h"

/// <summary>
/// タイトルのスタート画像
/// </summary>
class TitleStartImage : public GameObject
{
	////変数

	int hPict_Default_;			//デフォルト画像番号
	int hPict_A_Select_;		//A選択画像番号
	int hPict_RT_Select_;		//RT選択画像番号
	int hPict_All_Select_;		//全て選択画像番号
	std::string ModelNamePath_; //ファイルネームパス

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TitleStartImage(GameObject* parent, std::string modelPath, std::string name);

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

