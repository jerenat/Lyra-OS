#include <math.h>

double cos(double radians)
{
	double result = 0;
	double sign = 0;
	double x2n = 0;
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

		x2n = 1.0;
		for (count = 0; count < (2 * n); count += 1)
			x2n *= radians;

		factorial = 1.0;
		for (count = (2 * n); count > 0; count -= 1)
			factorial *= count;

		if (factorial)
			result += (sign * (x2n / factorial));
	}

	return (result);
}
