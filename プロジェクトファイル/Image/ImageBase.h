#pragma once
#include "../Engine/GameObject.h"

/// <summary>
/// 画像を表示させる基底クラス
/// </summary>
class ImageBase : public GameObject
{

	int hPict_;                   //画像番号
	std::string ModelNamePath_;   //ファイルネームパス

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	ImageBase(GameObject* parent, std::string modelPath, std::string name);

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
};

