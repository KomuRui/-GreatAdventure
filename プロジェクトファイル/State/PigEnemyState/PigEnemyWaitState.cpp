//#include "PigEnemyWaitState.h"
//#include "../../Engine/Input.h"
//#include "../../Engine/GameManager.h"
//#include "PigEnemyState.h"
//
////�X�V
//void PigEnemyWaitState::Update2D()
//{
//	HandleInput();
//}
//
////3D�p�X�V
//void PigEnemyWaitState::Update3D()
//{
//    //��Ԏ��Ԃ���ԕω��̎��Ԃ��傫���Ȃ�����
//    if (stateCount_ > operationTime_)
//    {
//        //0�ɏ�����
//        ZERO_INITIALIZE(operationTime_);
//
//        //��Ԃ�Move�ɕύX
//        ChangeState(PigEnemyState::pigEnemyState_, PigEnemyState::pigEnemyMove_);
//    }
//
//	HandleInput();
//}
//
////���͂ɂ���ď�ԕω�����
//void PigEnemyWaitState::HandleInput()
//{
//}
//
////��ԕω������Ƃ���񂾂��Ă΂��֐�
//void PigEnemyWaitState::Enter()
//{
//	operationTime_ = (rand() % 13 + 6) * 10;
//	ZERO_INITIALIZE(stateCount_);
//}