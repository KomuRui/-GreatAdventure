#pragma once
#include "../../../Engine/GameObject/GameObject.h"

//前定義
class EasingMove;

/// <summary>
/// ボス出現する時の警告イメージ
/// </summary>
class BossWarningImage : public GameObject
{

	int hWarningPict_; 	//警告画像番号
	int hBackGround_;   //背景
	int hTime_;         //タイマー番号
	int sign_;          //符号

	float backGroundAlpha_;     //背景の透明度

	EasingMove* pEasingMove_; 	//UIをイージングで移動させる用

	bool isEasingChange_;       //イージング変更したかどうか
	bool isFinish_;          	//最後まで動きが終わったかどうか

public:

	//コンストラクタ
	BossWarningImage(GameObject* parent);

	/////////////////////オーバーライドする関数///////////////////////////

	//初期化
	void Initialize() override;

	//更新の前に一回呼ばれる関数
	void StartUpdate() override {};

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override {};

	//////////////////////////関数///////////////////////////

	/// <summary>
	/// 背景透明度の計算
	/// </summary>
	void BackGroundAlphaCalc();

	/// <summary>
	/// 最後まで動きが終了したか
	/// </summary>
	/// <returns>trueなら終わっている</returns>
	bool isFinish() { return isFinish_; }
};

