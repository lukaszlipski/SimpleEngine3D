#include "vector2d.h"
#include <math.h>

namespace SE3D {

	Vector2D::Vector2D()
		: x(0), y(0)
	{
	}

	Vector2D::Vector2D(float a, float b)
		: x(a), y(b)
	{
	}

	float Vector2D::Length() const
	{
		return sqrtf(x*x + y*y);
	}

	float Vector2D::LengthSquared() const
	{
		return x*x + y*y;
	}

	float Vector2D::Dot(const Vector2D & right) const
	{
		return (this->x * right.x) + (this->y * right.y);
	}

	Vector2D Vector2D::Normalize() const
	{
		Vector2D newVec(this->x, this->y);
		float length = this->Length();
		newVec.x /= length;
		newVec.y /= length;
		return newVec;
	}

	Vector2D operator+(Vector2D left, const Vector2D & right)
	{
		return Vector2D(left.x + right.x, left.y + right.y);
	}

	Vector2D operator-(Vector2D left, const Vector2D & right)
	{
		return Vector2D(left.x - right.x, left.y - right.y);
	}

	Vector2D operator+(Vector2D left, float s)
	{
		return Vector2D(left.x + s, left.y + s);
	}

	Vector2D operator-(Vector2D left, float s)
	{
		return Vector2D(left.x - s, left.y - s);
	}

	Vector2D operator*(Vector2D left, float s)
	{
		return Vector2D(left.x * s, left.y * s);
	}

	Vector2D operator/(Vector2D left, float s)
	{
		return Vector2D(left.x / s, left.y / s);
	}

	Vector2D & Vector2D::operator+=(const Vector2D & right)
	{
		this->x += right.x;
		this->y += right.y;
		return *this;
	}

	Vector2D & Vector2D::operator-=(const Vector2D & right)
	{
		this->x -= right.x;
		this->y -= right.y;
		return *this;
	}

	Vector2D & Vector2D::operator+=(float s)
	{
		this->x += s;
		this->y += s;
		return *this;
	}

	Vector2D & Vector2D::operator-=(float s)
	{
		this->x -= s;
		this->y -= s;
		return *this;
	}

	Vector2D & Vector2D::operator*=(float s)
	{
		this->x *= s;
		this->y *= s;
		return *this;
	}

	Vector2D & Vector2D::operator/=(float s)
	{
		this->x /= s;
		this->y /= s;
		return *this;
	}

	bool operator==(Vector2D left, const Vector2D & right)
	{
		return (left.x == right.x && left.y == right.y);
	}

	bool operator!=(Vector2D left, const Vector2D & right)
	{
		return !(left == right);
	}

}