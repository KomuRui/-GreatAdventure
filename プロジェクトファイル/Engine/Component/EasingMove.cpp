#include "EasingMove.h"
#include "../Easing.h"
#include "../Time.h"

//�R���X�g���N�^
EasingMove::EasingMove(XMFLOAT3* targetPos, XMFLOAT3 beforePos, XMFLOAT3 afterPos, float moveTime, float (*func)(float))
	:targetPos_(targetPos),beforePos_(beforePos),afterPos_(afterPos),moveTime_(moveTime), easingFunc(func), nowTime_(ZERO)
{}


//�C�[�W���O���Ȃ���ړ�
bool EasingMove::Move()
{
	//�^�C�������b�N����Ă�����A�����b�N
	if (Time::isLock()) Time::UnLock();

	//�ǂ̂��炢�̊������Ԃ������������߂�(0�`1)
	ARGUMENT_INITIALIZE(nowTime_, (Time::GetTimef() / moveTime_));

	//�����Ō�܂ŏI����Ă����̂Ȃ�true��Ԃ�
	if (nowTime_ > 1) return true;

	//�ړ�
	ARGUMENT_INITIALIZE(*targetPos_,VectorToFloat3(XMVectorLerp(XMLoadFloat3(&beforePos_), XMLoadFloat3(&afterPos_),(*easingFunc)(nowTime_))));
}

//���Z�b�g
void EasingMove::Reset(XMFLOAT3* targetPos,XMFLOAT3 beforePos, XMFLOAT3 afterPos, float moveTime, float (*func)(float))
{

	//�e�ϐ�������
	ARGUMENT_INITIALIZE(targetPos_, targetPos);
	ARGUMENT_INITIALIZE(beforePos_,beforePos);
	ARGUMENT_INITIALIZE(afterPos_,afterPos);
	ARGUMENT_INITIALIZE(moveTime_,moveTime);
	ARGUMENT_INITIALIZE(easingFunc,func);
	ARGUMENT_INITIALIZE(nowTime_,ZERO);

	//�^�C��������
	Time::Reset();
	Time::Lock();
}


