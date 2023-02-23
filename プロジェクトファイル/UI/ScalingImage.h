#pragma once
#include "../Engine/GameObject/GameObject.h"
#include "ImageBase.h"

/// <summary>
/// 拡大縮小画像を表示させるクラス
/// </summary>
class ScalingImage : public ImageBase
{
	////変数

	XMVECTOR  beforeScale_;		  //補間する前の拡大率保存
	XMVECTOR  targetScale_;       //次の目標とする拡大率

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	ScalingImage(GameObject* parent, std::string modelPath, std::string name);

	//更新の前に一度だけ呼ばれる
	void ChildStartUpdate() override;

	//更新
	void ChildUpdate() override;
};

