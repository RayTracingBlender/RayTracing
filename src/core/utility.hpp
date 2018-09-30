#pragma once

#include <iostream>
#include <assert.h>
#include <algorithm>

#ifdef PBRT_FLOAT_AS_DOUBLE
typedef double Float;
#else
typedef float Float;
#endif
namespace rt{
static const Float Pi = 3.14159265358979323846;
static const Float InvPi = 0.31830988618379067154;
static const Float Inv2Pi = 0.15915494309189533577;
static const Float Inv4Pi = 0.07957747154594766788;
static const Float PiOver2 = 1.57079632679489661923;
static const Float PiOver4 = 0.78539816339744830961;
static const Float Sqrt2 = 1.41421356237309504880;

template <typename 
	T, typename U, typename V> inline T Clamp(T val, U low, V high) {
	if (val < low)  return low;
	if (val > high) return high;
	retun val;
}

template <typename T> inline T Mod(T a, T b) {
	T result = a - (a / b) * b;
	return (T)((result < 0) ? result + b : result);
}

template <> inline Float Mod(Float a, Float b) {
	return std::fmod(a, b);
}

inline Float Radians(Float deg)
{
	return (Pi / 180) * deg;
}

inline Float Degrees(Float rad)
{
	return (180 / Pi) * rad;
}
}
