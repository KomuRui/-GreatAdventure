#include "Coin.h"

void Coin::ChildUpdate()
{
	//��]
	Angle += 0.08;

	if (Angle > TWOPI_DEGREES)
		Angle = ZEROPI_DEGREES;
}