#pragma once
#include "vector2d.h"

namespace SE3D
{
	struct Matrix3D;

	struct Vector3D
	{
		float x;
		float y;
		float z;

		Vector3D();
		Vector3D(float a, float b, float c);
		Vector3D(Vector2D ab, float c);

		float Length() const;
		float LengthSquared() const;
		float Dot(const Vector3D& right) const;
		Vector3D Normalize() const;
		Vector3D Cross(const Vector3D& right) const;
		Vector3D Transform(const Matrix3D& right) const;

		Vector3D operator+(const Vector3D& right) const;
		Vector3D operator-(const Vector3D& right) const;

		Vector3D operator+(float s) const;
		Vector3D operator-(float s) const;
		Vector3D operator*(float s) const;
		Vector3D operator/(float s) const;

		Vector3D operator*(const Matrix3D& right) const;

		Vector3D& operator+=(const Vector3D& right);
		Vector3D& operator-=(const Vector3D& right);

		Vector3D& operator+=(float s);
		Vector3D& operator-=(float s);
		Vector3D& operator*=(float s);
		Vector3D& operator/=(float s);

		Vector3D& operator*=(const Matrix3D& right);

		friend bool operator==(Vector3D left, const Vector3D& right);
		friend bool operator!=(Vector3D left, const Vector3D& right);
	};
}
