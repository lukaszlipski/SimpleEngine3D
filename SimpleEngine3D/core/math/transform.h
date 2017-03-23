#pragma once
#include "vector3d.h"
#include "quaternion.h"

namespace SE3D
{
	struct Transform
	{
		Vector3D Position;
		Quaternion Rotation;
		Vector3D Scale;

		Transform();
		Transform(const Vector3D& position);
		Transform(const Vector3D& position, const Quaternion& rotation);
		Transform(const Vector3D& position, const Quaternion& rotation, const Vector3D& scale);

		Matrix4D GetMatrix() const;
		Transform Combine(const Transform& transform) const;

	};
}
