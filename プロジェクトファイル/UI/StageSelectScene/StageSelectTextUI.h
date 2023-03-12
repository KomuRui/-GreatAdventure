#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/ResourceManager/Text.h"

/// <summary>
/// ステージ選択シーンの文字UI
/// </summary>
class StageSelectTextUI : public GameObject
{
	//シーンの名前を表示するテキスト
	Text* sceneNameText;

public:

	//コンストラクタ
	StageSelectTextUI(GameObject* parent);

	/////////////////////オーバーライドする関数//////////////////////

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

