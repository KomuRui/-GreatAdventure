#pragma once
#include "State.h"

class RotationningState : public State
{
	int rotationCount_; //‰½Fps‰ñ“]‚µ‚Ä‚¢‚é‚©

public:

	//XV
	void Update2D() override;

	//“ü—Í‚É‚æ‚Á‚Äó‘Ô•Ï‰»‚·‚é
	void HandleInput() override;

	//ó‘Ô•Ï‰»‚µ‚½‚Æ‚«ˆê‰ñ‚¾‚¯ŒÄ‚Î‚ê‚éŠÖ”
	void Enter() override;
};

