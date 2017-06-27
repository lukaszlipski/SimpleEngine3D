#pragma once
#include "vector3d.h"


namespace SE3D
{
	struct Sphere
	{
		Vector3D center;
		float radius;

		Sphere()
			: center(Vector3D(0,0,0)), radius(1) {}

		Sphere(const Vector3D& c, float r)
			: center(c), radius(r) {}

	};
}