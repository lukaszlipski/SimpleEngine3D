#pragma once

#include "vector2d.h"
#include "vector3d.h"
#include "vector4d.h"
#include "matrix3d.h"
#include "matrix4d.h"

#define M_PI 3.14159265358979323846

namespace SE3D
{

	inline float ToRadians(float degree) { return (static_cast<float>(M_PI) / 180.0f) * degree; }
	inline float ToDegrees(float radian) { return (180.0f / static_cast<float>(M_PI)) * radian; }
	template<typename T> T Min(T a, T b) { return a < b ? a : b; }
	template<typename T> T Max(T a, T b) { return a > b ? a : b; }

	inline float Pow(float a, float b)
	{
		float result = a;
		for (int32 i = 1; i < b; ++i)
		{
			result *= a;
		}
		return result;
	}

	inline int32 Factorial(int32 x)
	{
		if (!x) return 1;
		int32 result = x;
		for (int32 i = x - 1; i > 0; --i)
		{
			result *= i;
		}
		return result;
	}

	inline float Cos(float x)
	{
		float result = 1.0f;
		float sign = -1.0f;
		for (int32 i = 2; i < 10; i+=2)
		{
			result = result + sign * ( Pow(x, static_cast<float>(i)) / static_cast<float>(Factorial(i)) );
			sign *= -1.0f;
		}
		return result;
	}

	inline float Sin(float x)
	{
		float result = x;
		float sign = -1.0f;
		for (int32 i = 3; i < 10; i += 2)
		{
			result = result + sign * (Pow(x, static_cast<float>(i)) / static_cast<float>(Factorial(i)));
			sign *= -1.0f;
		}
		return result;
	}

	inline float Tan(float x) {	return Sin(x) / Cos(x);	}

	inline float Exp(float x)
	{
		float result = 1.0f;
		for (int32 i = 1; i < 10; ++i)
		{
			result = result + Pow(x, static_cast<float>(i)) / static_cast<float>(Factorial(i));
		}
		return result;
	}

	inline float Sqrt(float x) {
		float lower;
		float upper;
		float y;

		if (x < 1.0f)
		{
			lower = x;
			upper = 1;
		}
		else
		{
			lower = 1;
			upper = x;
		}

		while ((upper - lower) > 0.001f)
		{
			y = (upper + lower) / 2.0f;
			if (Pow(y, 2) > x)
			{
				upper = y;
			}
			else
			{
				lower = y;
			}
		}
		return (upper + lower) / 2.0f;
	}


}
