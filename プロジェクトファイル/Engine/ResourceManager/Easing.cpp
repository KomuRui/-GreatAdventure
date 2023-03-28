#include "Easing.h"
#include "Global.h"
#include <cmath>
#include <algorithm>
#define M_PI 3.14159265359

//イージング(緩急みたいなもの)
namespace Easing
{
	float InSine(float x)
	{
		ARGUMENT_INITIALIZE(x, min(1, x));
		ARGUMENT_INITIALIZE(x, max(0, x));
		return (float)(1 - cos((x * M_PI) / 2));
	}

	float OutSine(float x)
	{
		ARGUMENT_INITIALIZE(x, min(1, x));
		ARGUMENT_INITIALIZE(x, max(0, x));
		return (float)(sin((x * M_PI) / 2));
	}

	float InOutSine(float x)
	{
		ARGUMENT_INITIALIZE(x, min(1, x));
		ARGUMENT_INITIALIZE(x, max(0, x));
		return (float)(-(cos(M_PI * x) - 1) / 2);
	}

	float InQuad(float x)
	{
		ARGUMENT_INITIALIZE(x, min(1, x));
		ARGUMENT_INITIALIZE(x, max(0, x));
		return (float)(x * x);
	}

	float OutQuad(float x)
	{
		ARGUMENT_INITIALIZE(x, min(1, x));
		ARGUMENT_INITIALIZE(x, max(0, x));
		return (float)(1 - (1 - x) * (1 - x));
	}

	float InOutQuad(float x)
	{
		ARGUMENT_INITIALIZE(x, min(1, x));
		ARGUMENT_INITIALIZE(x, max(0, x));
		return (float)((x < 0.5) ? 2 * x * x : 1 - pow(-2 * x + 2, 2) / 2);
	}

	float InCubic(float x)
	{
		ARGUMENT_INITIALIZE(x, min(1, x));
		ARGUMENT_INITIALIZE(x, max(0, x));
		return (float)(x * x * x);
	}

	float OutCubic(float x)
	{
		ARGUMENT_INITIALIZE(x, min(1, x));
		ARGUMENT_INITIALIZE(x, max(0, x));
		return (float)(1 - pow(1 - x, 3));
	}

	float InOutCubic(float x)
	{
		ARGUMENT_INITIALIZE(x, min(1, x));
		ARGUMENT_INITIALIZE(x, max(0, x));
		return (float)((x < 0.5) ? 4 * x * x * x : 1 - pow(-2 * x + 2, 3) / 2);
	}

	float InQuart(float x)
	{
		ARGUMENT_INITIALIZE(x, min(1, x));
		ARGUMENT_INITIALIZE(x, max(0, x));
		return (float)(x * x * x * x);
	}

	float OutQuart(float x)
	{
		ARGUMENT_INITIALIZE(x, min(1, x));
		ARGUMENT_INITIALIZE(x, max(0, x));
		return (float)(1 - pow(1 - x, 4));
	}

	float InOutQuart(float x)
	{
		ARGUMENT_INITIALIZE(x, min(1, x));
		ARGUMENT_INITIALIZE(x, max(0, x));
		return (float)((x < 0.5) ? 8 * x * x * x * x : 1 - pow(-2 * x + 2, 4) / 2);
	}

	float InQuint(float x)
	{
		ARGUMENT_INITIALIZE(x, min(1, x));
		ARGUMENT_INITIALIZE(x, max(0, x));
		return (float)(x * x * x * x * x);
	}

	float OutQuint(float x)
	{
		ARGUMENT_INITIALIZE(x, min(1, x));
		ARGUMENT_INITIALIZE(x, max(0, x));
		return (float)(1 - pow(1 - x, 5));
	}

	float InOutQuint(float x)
	{
		ARGUMENT_INITIALIZE(x, min(1, x));
		ARGUMENT_INITIALIZE(x, max(0, x));
		return (float)((x < 0.5) ? 16 * x * x * x * x * x : 1 - pow(-2 * x + 2, 5) / 2);
	}

	float InExpo(float x)
	{
		ARGUMENT_INITIALIZE(x, min(1, x));
		ARGUMENT_INITIALIZE(x, max(0, x));
		return (float)((x == 0) ? 0 : pow(2, 10 * x - 10));
	}

	float OutExpo(float x)
	{
		ARGUMENT_INITIALIZE(x, min(1, x));
		ARGUMENT_INITIALIZE(x, max(0, x));
		return (float)((x == 1) ? 1 : 1 - pow(2, -10 * x));
	}

	float InOutExpo(float x)
	{
		ARGUMENT_INITIALIZE(x, min(1, x));
		ARGUMENT_INITIALIZE(x, max(0, x));
		return (float)(x ==  0 ? 0
			           : x == 1 ? 1
								: x < 0.5 ? pow(2, 20 * x - 10) / 2
								: (2 - pow(2, -20 * x + 10)) / 2);
	}

	float InCirc(float x)
	{
		ARGUMENT_INITIALIZE(x, min(1, x));
		ARGUMENT_INITIALIZE(x, max(0, x));
		return (float)(1 - sqrt(1 - pow(x, 2)));
	}

	float OutCirc(float x)
	{
		ARGUMENT_INITIALIZE(x, min(1, x));
		ARGUMENT_INITIALIZE(x, max(0, x));
		return (float)(sqrt(1 - pow(x - 1, 2)));
	}

	float InOutCirc(float x)
	{
		ARGUMENT_INITIALIZE(x, min(1, x));
		ARGUMENT_INITIALIZE(x, max(0, x));
		return (float)(x < 0.5
			? (1 - sqrt(1 - pow(2 * x, 2))) / 2
			: (sqrt(1 - pow(-2 * x + 2, 2)) + 1) / 2);
	}

	float InBack(float x)
	{
		ARGUMENT_INITIALIZE(x, min(1, x));
		ARGUMENT_INITIALIZE(x, max(0, x));

		float c1 = 1.70158f;
		float c3 = c1 + 1;

		return (float)(c3 * x * x * x - c1 * x * x);
	}

	float OutBack(float x)
	{
		ARGUMENT_INITIALIZE(x, min(1, x));
		ARGUMENT_INITIALIZE(x, max(0, x));

		float c1 = 1.70158f;
		float c3 = c1 + 1;

		return (float)(1 + c3 * pow(x - 1, 3) + c1 * pow(x - 1, 2));
	}

	float InOutBack(float x)
	{
		ARGUMENT_INITIALIZE(x, min(1, x));
		ARGUMENT_INITIALIZE(x, max(0, x));

		float c1 = 1.70158f;
		float c2 = c1 * 1.525f;

		return (float)(x < 0.5
			? (pow(2 * x, 2) * ((c2 + 1) * 2 * x - c2)) / 2
			: (pow(2 * x - 2, 2) * ((c2 + 1) * (x * 2 - 2) + c2) + 2) / 2);
	}

	float InElastic(float x)
	{
		ARGUMENT_INITIALIZE(x, min(1, x));
		ARGUMENT_INITIALIZE(x, max(0, x));

		float c4 = (float)((2 * M_PI) / 3.0f);

		return (float)(x == 0
			? 0
			: x == 1
			? 1
			: -pow(2, 10 * x - 10) * sin((x * 10 - 10.75) * c4));
	}

	float OutElastic(float x)
	{
		ARGUMENT_INITIALIZE(x, min(1, x));
		ARGUMENT_INITIALIZE(x, max(0, x));

		float c4 = (float)((2 * M_PI) / 3.0f);

		return (float)(x == 0
			? 0
			: x == 1
			? 1
			: pow(2, -10 * x) * sin((x * 10 - 0.75) * c4) + 1);
	}

	float InOutElastic(float x)
	{
		ARGUMENT_INITIALIZE(x, min(1, x));
		ARGUMENT_INITIALIZE(x, max(0, x));

		float c5 = (float)((2 * M_PI) / 4.5f);

		return (float)(x == 0
			? 0
			: x == 1
			? 1
			: x < 0.5
			? -(pow(2, 20 * x - 10) * sin((20 * x - 11.125) * c5)) / 2
			: (pow(2, -20 * x + 10) * sin((20 * x - 11.125) * c5)) / 2 + 1);
	}

	float InBounce(float x)
	{
		ARGUMENT_INITIALIZE(x, min(1, x));
		ARGUMENT_INITIALIZE(x, max(0, x));

		return (float)(1 - OutBounce(1 - x));
	}

	float OutBounce(float x) 
	{
		ARGUMENT_INITIALIZE(x, min(1, x));
		ARGUMENT_INITIALIZE(x, max(0, x));

		float n1 = 7.5625;
		float d1 = 2.75;

		if (x < 1 / d1) {
			return (float)(n1 * x * x);
		}
		else if (x < 2 / d1) {
			return (float)(n1 * (x -= 1.5f / d1) * x + 0.75f);
		}
		else if (x < 2.5 / d1) {
			return (float)(n1 * (x -= 2.25f / d1) * x + 0.9375f);
		}
		else {
			return (float)(n1 * (x -= 2.625f / d1) * x + 0.984375f);
		}
	}

	float InOutBounce(float x)
	{
		ARGUMENT_INITIALIZE(x, min(1, x));
		ARGUMENT_INITIALIZE(x, max(0, x));

		return (float)(x < 0.5
			? (1 - OutBounce(1 - 2 * x)) / 2
			: (1 + OutBounce(2 * x - 1)) / 2);
	}
};