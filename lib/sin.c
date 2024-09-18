#include <math.h>

double sin(double radians)
{
	double result = 0;
	double sign = 0;
	double x2nplus1 = 0;
	double factorial = 0;
	double n, count;

	while (radians > (M_PI * 2))
		radians -= (M_PI * 2);
	while (radians < -(M_PI * 2))
		radians += (M_PI * 2);

	for (n = 0; n < 15; n += 1)
	{
		sign = 1.0;
		for (count = 0; count < n; count += 1)
			sign *= -1;

		x2nplus1 = 1.0;
		for (count = 0; count < ((2 * n) + 1); count += 1)
			x2nplus1 *= radians;

		factorial = 1.0;
		for (count = ((2 * n) + 1); count > 0; count -= 1)
			factorial *= count;

		if (factorial)
			result += (sign * (x2nplus1 / factorial));
	}

	return (result);
}