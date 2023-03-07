#pragma once
#include "../../Engine/GameObject/GameObject.h"

/// <summary>
/// 最後のお姫様と出会うMovieを流すシーン
/// </summary>
class LastScene : public GameObject
{

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	LastScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新の前に一度だけ呼ばれる関数
	void StartUpdate() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

};

