#pragma once
#include "../../Engine/GameObject.h"

//■■シーンを管理するクラス
class UserSelectScene : public GameObject
{
	//モデル番号格納用
	int hModel_;

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	UserSelectScene(GameObject* parent);

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