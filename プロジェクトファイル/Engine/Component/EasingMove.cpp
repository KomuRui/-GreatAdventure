#include "EasingMove.h"
#include "../ResourceManager/Easing.h"
#include "../ResourceManager/Time.h"

//コンストラクタ
EasingMove::EasingMove()
	:targetPos_(nullptr), beforePos_(XMFLOAT3(ZERO, ZERO, ZERO)), afterPos_(XMFLOAT3(ZERO, ZERO, ZERO)), moveTime_(ZERO), easingFunc(Easing::InBack), nowTime_(ZERO), timerhNum_((int)ZERO)
{}

//コンストラクタ
EasingMove::EasingMove(XMFLOAT3* targetPos, XMFLOAT3 beforePos, XMFLOAT3 afterPos, float moveTime, float (*func)(float))
	:targetPos_(targetPos),beforePos_(beforePos),afterPos_(afterPos),moveTime_(moveTime), easingFunc(func), nowTime_(ZERO), timerhNum_((int)ZERO)
{
	//タイマー作成
	ARGUMENT_INITIALIZE(timerhNum_,Time::Add());
}


//イージングしながら移動
bool EasingMove::Move()
{
	//タイムがロックされていたらアンロック
	if (Time::isLock(timerhNum_)) Time::UnLock(timerhNum_);

	//どのくらいの割合時間がたったか求める(0～1)
	ARGUMENT_INITIALIZE(nowTime_, (Time::GetTimef(timerhNum_) / moveTime_));

	//もし最後まで終わっていたのならtrueを返す
	if (nowTime_ > 1) return true;

	//移動
	ARGUMENT_INITIALIZE(*targetPos_,VectorToFloat3(XMVectorLerp(XMLoadFloat3(&beforePos_), XMLoadFloat3(&afterPos_),(*easingFunc)(nowTime_))));


	return false;
}

//リセット
void EasingMove::Reset(XMFLOAT3* targetPos,XMFLOAT3 beforePos, XMFLOAT3 afterPos, float moveTime, float (*func)(float))
{
	//各変数初期化
	ARGUMENT_INITIALIZE(targetPos_, targetPos);
	ARGUMENT_INITIALIZE(beforePos_,beforePos);
	ARGUMENT_INITIALIZE(afterPos_,afterPos);
	ARGUMENT_INITIALIZE(moveTime_,moveTime);
	ARGUMENT_INITIALIZE(easingFunc,func);
	ARGUMENT_INITIALIZE(nowTime_,ZERO);

	//タイム初期化
	Time::Reset(timerhNum_);
	Time::Lock(timerhNum_);
}


