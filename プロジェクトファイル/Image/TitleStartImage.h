#pragma once
#include "../Engine/GameObject.h"

class TitleStartImage : public GameObject
{
	//使う画像の種類
	enum type
	{
		Default,
		A_Select,
		RT_Select,
		All_Select,
		MAX_IMAGE_TYPE
	};

	////定数

	const XMFLOAT3 BEFORE_SCALE = { 1.0,1.0,1.0 };
	const XMFLOAT3 AFTER_SCALE = { 1.1,1.1,1.1 };

	////変数

	int hPict_[MAX_IMAGE_TYPE];   //画像番号
	std::string ModelNamePath_;   //ファイルネームパス

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

