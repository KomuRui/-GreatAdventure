#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Fade.h"
#include "../Button.h"

//■■シーンを管理するクラス
class HomeScene : public GameObject
{

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	HomeScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新の前に一度だけ呼ばれる
	void StartUpdate() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

};

