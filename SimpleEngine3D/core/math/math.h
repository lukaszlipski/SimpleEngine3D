#pragma once

#include "vector2d.h"
#include "vector3d.h"
#include "vector4d.h"
#include "matrix3d.h"
#include "matrix4d.h"

#define M_PI 3.14159265358979323846

namespace SE3D {
	inline float ToRadians(float degree) { return ((float)M_PI / 180.0f) * degree; }
	inline float ToDegrees(float radian) { return (180.0f / (float)M_PI) * radian; }
}