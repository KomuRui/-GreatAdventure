#pragma once
#include "PlayerState.h"

class StandingState : public PlayerState
{
public:

	//XV
	void Update() override;

	//“ü—Í‚É‚æ‚Á‚Äó‘Ô•Ï‰»‚·‚é
	void HandleInput() override;
};

