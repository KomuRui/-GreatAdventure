#pragma once
#include "State.h"

class RotationningState : public State
{
public:

	//XV
	void Update() override;

	//“ü—Í‚É‚æ‚Á‚Äó‘Ô•Ï‰»‚·‚é
	void HandleInput() override;

	//ó‘Ô•Ï‰»‚µ‚½‚Æ‚«ˆê‰ñ‚¾‚¯ŒÄ‚Î‚ê‚éŠÖ”
	void Enter() override;
};

