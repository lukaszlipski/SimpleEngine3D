#pragma once
#include "matrix4d.h"

namespace SE3D
{
	struct Quaternion
	{
		float x;
		float y;
		float z;
		float w;
		
		Quaternion();
		Quaternion(float x, float y, float z, float w);
		Quaternion(Vector3D axis, float angle);
		Quaternion(const Quaternion& quaternion);

		float Length() const;
		Quaternion Normalize() const;
		Quaternion Conjugate() const;
		Matrix4D ToRotationMatrix() const;

		Vector3D GetRight() const;
		Vector3D GetForward() const;

		friend Quaternion operator+(Quaternion left, const Quaternion& right);
		friend Quaternion operator-(Quaternion left, const Quaternion& right);
		friend Quaternion operator*(Quaternion left, const Quaternion& right);
		friend Quaternion operator*(Quaternion left, const Vector3D& right);
		friend Quaternion operator*(Quaternion left, float s);
		friend Quaternion operator/(Quaternion left, float s);

		Quaternion& operator+=(const Quaternion& right);
		Quaternion& operator-=(const Quaternion& right);
		Quaternion& operator*=(const Quaternion& right);
		Quaternion& operator*=(const Vector3D& right);
		Quaternion& operator*=(float s);
		Quaternion& operator/=(float s);

		friend bool operator==(Quaternion left, const Quaternion& right);
		friend bool operator!=(Quaternion left, const Quaternion& right);

	};
}
