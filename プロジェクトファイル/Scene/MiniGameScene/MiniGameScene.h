#pragma once
#include "../../Engine/GameObject/GameObject.h"

/// <summary>
/// ミニゲームシーン
/// </summary>
class MiniGameScene : public GameObject
{

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	MiniGameScene(GameObject* parent);

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

