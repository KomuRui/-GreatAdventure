#pragma once
#include "Image.h"
#include <vector>

class Fade
{
	float strong2;
	float move2;

public:

	Fade() { strong2 = 0; move2 = 1; }

	void FadeIn(int handle, float ratio = 1.0);

	void FadeOut(int handle, float ratio = 1.0);

	void FadeInOut(int handle, float ratio = 1.0);

};

