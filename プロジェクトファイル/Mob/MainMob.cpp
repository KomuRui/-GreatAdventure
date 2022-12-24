#include "MainMob.h"

//定数
namespace
{
	static const int START_FRAME = 0;	  //開始フレーム
	static const int END_FRAME = 120;     //終了フレーム
	static const float ANIM_SPEED = 1.0f; //アニメーションの再生速度
}

//更新の前に一度だけ呼ばれる
void MainMob::ChildStartUpdate()
{
	//アニメーション
	Model::SetAnimFrame(hModel_, START_FRAME, END_FRAME, ANIM_SPEED);
	Model::SetAnimFlag(hModel_, true);
}
