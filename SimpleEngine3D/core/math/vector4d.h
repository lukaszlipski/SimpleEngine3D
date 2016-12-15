#pragma once

#include "vector2d.h"
#include "vector3d.h"

namespace SE3D {

	struct Vector4D
	{
		float x;
		float y;
		float z;
		float w;

		Vector4D();
		Vector4D(float a, float b, float c, float w);
		Vector4D(Vector2D ab, float c, float d);
		Vector4D(Vector3D abc, float d);

		float Dot(const Vector4D& right) const;

		friend Vector4D operator+(Vector4D left, const Vector4D& right);
		friend Vector4D operator-(Vector4D left, const Vector4D& right);

		friend Vector4D operator+(Vector4D left, float s);
		friend Vector4D operator-(Vector4D left, float s);
		friend Vector4D operator*(Vector4D left, float s);
		friend Vector4D operator/(Vector4D left, float s);

		Vector4D& operator+=(const Vector4D& right);
		Vector4D& operator-=(const Vector4D& right);

		Vector4D& operator+=(float s);
		Vector4D& operator-=(float s);
		Vector4D& operator*=(float s);
		Vector4D& operator/=(float s);

		friend bool operator==(Vector4D left, const Vector4D& right);
		friend bool operator!=(Vector4D left, const Vector4D& right);
	};

}