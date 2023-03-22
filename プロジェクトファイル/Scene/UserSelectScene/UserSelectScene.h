#pragma once
#include "../../Engine/GameObject/GameObject.h"

/// <summary>
/// ユーザセレクト
/// </summary>
class UserSelectScene : public GameObject
{

	int hAudio_;    //音番号

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	UserSelectScene(GameObject* parent);

	//デストラクタ
	~UserSelectScene();

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