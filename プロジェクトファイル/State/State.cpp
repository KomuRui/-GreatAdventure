#include "State.h"

//��ԕύX
void State::ChangeState(State* nowState, State* state)
{
	//��ԕύX
	ARGUMENT_INITIALIZE(nowState, state);

	//��ԕω������Ƃ���񂾂��Ă΂��֐����Ă�
	nowState->Enter();
}
