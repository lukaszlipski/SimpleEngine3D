#pragma once

#include "vector2d.h"
#include "vector3d.h"
#include "vector4d.h"
#include "matrix3d.h"
#include "matrix4d.h"
#include <math.h>

#define M_PI 3.14159265358979323846

namespace SE3D
{
	inline float ToRadians(float degree) { return (static_cast<float>(M_PI) / 180.0f) * degree; }
	inline float ToDegrees(float radian) { return (180.0f / static_cast<float>(M_PI)) * radian; }
	template<typename T> T Min(T a, T b) { return a < b ? a : b; }
	template<typename T> T Max(T a, T b) { return a > b ? a : b; }
}
