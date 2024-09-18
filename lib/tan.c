#include <math.h>

double tan(double radians)
{
	// Returns the tan of x (x given in radians).
	return (sin(radians) / cos(radians));
}
