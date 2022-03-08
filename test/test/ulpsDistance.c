// Source for function: https://bitbashing.io/comparing-floats.html
#include "ulpsDistance.h"
#include <limits.h>
#include <math.h>
#include <string.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif // __GNUC__ || defined (__clang__)

int32_t ulpsDistanceFloat(const float a, const float b)
{
	// We can skip all the following work if they're equal.
	if(a == b)
		return 0;

	// We first check if the values are NaN.
	// If this is the case, they're inherently unequal;
	// return the maximum distance between the two.
	if(isnan(a) || isnan(b))
		return INT32_MAX;

	// If one's infinite, and they're not equal,
	// return the max distance between the two.
	if(isinf(a) || isinf(b))
		return INT32_MAX;

	// At this point we know that the floating-point values aren't equal and
	// aren't special values (infinity/NaN).
	// Because of how IEEE754 floats are laid out
	// (sign bit, then exponent, then mantissa), we can examine the bits
	// as if they were integers to get the distance between them in units
	// of least precision (ULPs).
	_Static_assert(sizeof(float) == sizeof(int32_t), "What size is float?");

	// memcpy to get around the strict aliasing rule.
	// The compiler knows what we're doing and will just transfer the float
	// values into integer registers.
	int32_t ia, ib;
	memcpy(&ia, &a, sizeof(float));
	memcpy(&ib, &b, sizeof(float));

	// If the signs of the two values aren't the same,
	// return the maximum distance between the two.
	// This is done to avoid integer overflow, and because the bit layout of
	// floats is closer to sign-magnitude than it is to two's complement.
	// This *also* means that if you're checking if a value is close to zero,
	// you should probably just use a fixed epsilon instead of this function.
	if((ia < 0) != (ib < 0))
		return INT32_MAX;

	// If we've satisfied all our caveats above, just subtract the values.
	// The result is the distance between the values in ULPs.
	int32_t distance = ia - ib;
	if(distance < 0)
		distance = -distance;
	return distance;
}

int64_t ulpsDistanceDouble(const double a, const double b)
{
	// We can skip all the following work if they're equal.
	if(a == b)
		return 0;

	// We first check if the values are NaN.
	// If this is the case, they're inherently unequal;
	// return the maximum distance between the two.
	if(isnan(a) || isnan(b))
		return INT64_MAX;

	// If one's infinite, and they're not equal,
	// return the max distance between the two.
	if(isinf(a) || isinf(b))
		return INT64_MAX;

	// At this point we know that the floating-point values aren't equal and
	// aren't special values (infinity/NaN).
	// Because of how IEEE754 floats are laid out
	// (sign bit, then exponent, then mantissa), we can examine the bits
	// as if they were integers to get the distance between them in units
	// of least precision (ULPs).
	_Static_assert(sizeof(double) == sizeof(int64_t), "What size is double?");

	// memcpy to get around the strict aliasing rule.
	// The compiler knows what we're doing and will just transfer the float
	// values into integer registers.
	int64_t ia, ib;
	memcpy(&ia, &a, sizeof(double));
	memcpy(&ib, &b, sizeof(double));

	// If the signs of the two values aren't the same,
	// return the maximum distance between the two.
	// This is done to avoid integer overflow, and because the bit layout of
	// floats is closer to sign-magnitude than it is to two's complement.
	// This *also* means that if you're checking if a value is close to zero,
	// you should probably just use a fixed epsilon instead of this function.
	if((ia < 0) != (ib < 0))
		return INT64_MAX;

	// If we've satisfied all our caveats above, just subtract the values.
	// The result is the distance between the values in ULPs.
	int64_t distance = ia - ib;

	if(distance < 0)
		distance = -distance;
	return distance;
}

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif // __GNUC__ || __clang__
