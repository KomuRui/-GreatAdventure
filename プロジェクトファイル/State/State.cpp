#include "State.h"

//ó‘Ô•ÏX
void State::ChangeState(State* nowState, State* state)
{
	//ó‘Ô•ÏX
	ARGUMENT_INITIALIZE(nowState, state);

	//ó‘Ô•Ï‰»‚µ‚½‚Æ‚«ˆê‰ñ‚¾‚¯ŒÄ‚Î‚ê‚éŠÖ”‚ğŒÄ‚Ô
	nowState->Enter();
}
