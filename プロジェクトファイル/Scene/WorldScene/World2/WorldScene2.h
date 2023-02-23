#pragma once
#include "../../../Engine/GameObject/GameObject.h"

//ボスが出現するクラス
class WorldScene2 : public GameObject
{

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	WorldScene2(GameObject* parent);

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

