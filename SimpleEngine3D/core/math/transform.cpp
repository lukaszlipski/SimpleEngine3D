#include "transform.h"

namespace SE3D
{

	Transform::Transform()
		: Position(Vector3D()), Rotation(Quaternion()), Scale(1, 1, 1)
	{
	}

	Transform::Transform(const Vector3D& position)
		: Position(position), Rotation(Quaternion()), Scale(1, 1, 1)
	{
	}

	Transform::Transform(const Vector3D& position, const Quaternion& rotation)
		: Position(position), Rotation(rotation), Scale(1, 1, 1)
	{
	}

	Transform::Transform(const Vector3D& position, const Quaternion& rotation, const Vector3D& scale)
		: Position(position), Rotation(rotation), Scale(scale)
	{
	}

	Matrix4D Transform::GetMatrix() const
	{
		return Matrix4D::ScaleMatrix(Scale) * Rotation.ToRotationMatrix() * Matrix4D::TranslateMatrix(Position);
	}

}
