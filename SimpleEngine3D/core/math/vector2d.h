#pragma once

namespace SE3D {

	struct Vector2D
	{
		float x;
		float y;

		Vector2D();
		Vector2D(float a,float b);

		float Length();
		float LengthSquared();
		float Dot(const Vector2D& right);
		Vector2D Normalize();

		Vector2D operator+(const Vector2D& right);
		Vector2D operator-(const Vector2D& right);

		Vector2D operator+(float s);
		Vector2D operator-(float s);
		Vector2D operator*(float s);
		Vector2D operator/(float s);

		Vector2D& operator+=(const Vector2D& right);
		Vector2D& operator-=(const Vector2D& right);

		Vector2D& operator+=(float s);
		Vector2D& operator-=(float s);
		Vector2D& operator*=(float s);
		Vector2D& operator/=(float s);

		bool operator==(const Vector2D& right);
	};

}