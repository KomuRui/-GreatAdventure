#pragma once
#include "../../Engine/GameObject.h"
#include "../../Engine/Fade.h"
#include "../../Button.h"

//■■シーンを管理するクラス
class TitleScene : public GameObject
{
	//モデル番号格納用
	int hModel_;

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TitleScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void StartUpdate() override;
};

