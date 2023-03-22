#pragma once
#include "../../../Engine/GameObject/GameObject.h"

/// <summary>
/// WorldScene1
/// </summary>
class WorldScene1 : public GameObject
{

	int hAudio_;    //音番号

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	WorldScene1(GameObject* parent);

	//デストラクタ
	~WorldScene1();

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

