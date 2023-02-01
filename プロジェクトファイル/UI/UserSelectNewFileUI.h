#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Text.h"

class CreateStage;

/// <summary>
/// ユーザー情報選択シーンの新しいファイルを作成する時のUI
/// </summary>
class UserSelectNewFileUI : public GameObject
{
	//UIとか表示する用
	CreateStage* pCreateStage_;

public:

	//コンストラクタ
	UserSelectNewFileUI(GameObject* parent);

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

