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

		float Length();
		float LengthSquared();
		float Dot(const Vector3D& right);
		Vector3D Normalize();
		Vector3D Cross(const Vector3D& right);

		Vector3D operator+(const Vector3D& right);
		Vector3D operator-(const Vector3D& right);

		Vector3D operator+(float s);
		Vector3D operator-(float s);
		Vector3D operator*(float s);
		Vector3D operator/(float s);

		Vector3D& operator+=(const Vector3D& right);
		Vector3D& operator-=(const Vector3D& right);

		Vector3D& operator+=(float s);
		Vector3D& operator-=(float s);
		Vector3D& operator*=(float s);
		Vector3D& operator/=(float s);

		bool operator==(const Vector3D& right);
	};

}