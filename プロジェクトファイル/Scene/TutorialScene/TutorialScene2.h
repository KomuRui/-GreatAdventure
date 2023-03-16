#pragma once
#include "../../Engine/GameObject/GameObject.h"

/// <summary>
/// チュートリアルシーン2
/// </summary>
class TutorialScene2 : public GameObject
{

	int hAudio_; //音番号

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TutorialScene2(GameObject* parent);

	//デストラクタ
	~TutorialScene2();

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

