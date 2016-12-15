#pragma once

namespace SE3D {

	struct Vector2D
	{
		float x;
		float y;

		Vector2D();
		Vector2D(float a,float b);

		float Length() const;
		float LengthSquared() const;
		float Dot(const Vector2D& right) const;
		Vector2D Normalize() const;

		friend Vector2D operator+(Vector2D left, const Vector2D& right);
		friend Vector2D operator-(Vector2D left, const Vector2D& right);

		friend Vector2D operator+(Vector2D left, float s);
		friend Vector2D operator-(Vector2D left, float s);
		friend Vector2D operator*(Vector2D left, float s);
		friend Vector2D operator/(Vector2D left, float s);

		Vector2D& operator+=(const Vector2D& right);
		Vector2D& operator-=(const Vector2D& right);

		Vector2D& operator+=(float s);
		Vector2D& operator-=(float s);
		Vector2D& operator*=(float s);
		Vector2D& operator/=(float s);

		friend bool operator==(Vector2D left, const Vector2D& right);
		friend bool operator!=(Vector2D left, const Vector2D& right);
	};

}