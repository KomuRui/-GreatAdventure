#include "Coin.h"

void Coin::UpdateMove()
{
	//��]
	Angle += 0.08;

	if (Angle > TWOPI_DEGREES)
		Angle = ZEROPI_DEGREES;
}