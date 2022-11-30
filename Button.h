#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fade.h"

//■■シーンを管理するクラス
class Button : public GameObject
{
protected:

	//画像番号
	int hPict_;

	//ファイル名
	std::string fileNamePas;

	//今選択されているか
	bool controllerSelect;

	//フェードするのに必要なやつ
	Fade* pfadeButton;

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Button(GameObject* parent);
	Button(GameObject* parent, std::string name);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void StartUpdate() override;

	//ボタンが押されたら何するか
	virtual void IsButtonPush() = 0;

	//ボタンが選択されているとき何をするか
	//デフォルト：フェードインアウトを繰り返す(継承したときにoverrideすれば中身変えれる)
	virtual void IsButtonSelect();

	//選択されているかをセット
	void SetSelect(const bool& flag) { controllerSelect = flag; }

	//選択されているかを確認
	bool GetSelect() { return controllerSelect; }
};