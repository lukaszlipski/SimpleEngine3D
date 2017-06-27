#pragma once
#include "vector3d.h"

namespace SE3D
{
	struct Plane
	{
		Vector3D point;
		Vector3D normal;

		inline float GetD() { return (normal * -1).Dot(point); }
		inline float Distance(const Vector3D& p) { return normal.Dot(p) + GetD(); }

	};
}