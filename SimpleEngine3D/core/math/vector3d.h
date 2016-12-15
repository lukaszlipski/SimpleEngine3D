#pragma once
#include "vector2d.h"

namespace SE3D {

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

		friend Vector3D operator+(Vector3D left, const Vector3D& right);
		friend Vector3D operator-(Vector3D left, const Vector3D& right);

		friend Vector3D operator+(Vector3D left, float s);
		friend Vector3D operator-(Vector3D left, float s);
		friend Vector3D operator*(Vector3D left, float s);
		friend Vector3D operator/(Vector3D left, float s);

		Vector3D& operator+=(const Vector3D& right);
		Vector3D& operator-=(const Vector3D& right);

		Vector3D& operator+=(float s);
		Vector3D& operator-=(float s);
		Vector3D& operator*=(float s);
		Vector3D& operator/=(float s);

		friend bool operator==(Vector3D left, const Vector3D& right);
		friend bool operator!=(Vector3D left, const Vector3D& right);
	};

}