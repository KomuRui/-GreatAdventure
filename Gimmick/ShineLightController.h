#pragma once
#include "ShineLight.h"
#include "../Engine/GameObject.h"

//光るライトギミックをコントロールするクラス
class ShineLightController : public GameObject
{
	//光るライトをすべて保管しておく変数(第一:ライトのオブジェクト,第二:光っているかどうか)
	std::vector<std::pair<ShineLight*,bool>> controller_;

	//光るライトをセットした順にそのオブジェクトのモデルパスネームを保存
	//Playerが光らせるときにこのvectorに入った順番に光らせないといけないため保存しておく
	std::vector<std::string> modelPathName_;

	//今何番目を見ているか
	int nowNumber_;

	//順番通りに光らせることが出来たか
	bool success_;

	//調べるかどうか
	bool checkFlag_;

public:

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

	//指定した時間で呼ばれるメソッド
	void TimeMethod() override;

	////////////////////関数//////////////////////

	//コンストラクタ
	ShineLightController(GameObject* parent);

	//すべて光っているか調べる
	bool AllCheckShine(); 

	//順番通り光らせているか調べる
	void CheckinOrderShine();

	////////////////////セッターゲッター//////////////////////

	//自身のcontroller_に追加
	void SetShineLight(ShineLight* shine) { std::pair<ShineLight*, bool> a = { shine, false }; controller_.push_back(a); modelPathName_.push_back(a.first->GetModelPathName()); }
};

