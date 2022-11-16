#pragma once
#include "Text.h"

class Time
{
private:

	//タイムを格納するための変数
	float time_;

	//文字を表示するための変数
	Text* text_;

	//タイムflag;
	bool Timeflag_;
	
public:

	//コンストラクタ
	Time() {}

	//デストラクタ
	~Time() { delete text_; }

	//初期化
	void Initialize() { text_ = new Text; text_->Initialize(); time_ = 0; Timeflag_ = false; }

	//タイムの描画
	//第1引数:表示位置X
	//第2引数:表示位置Y
	//第3引数:小数点第何まで表示
	void TimeDraw(int x, int y);

	//セッター
	void SetTimeflag(bool flag) { Timeflag_ = flag; }
};

