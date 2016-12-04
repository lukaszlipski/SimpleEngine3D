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

	float Vector2D::Length()
	{
		return sqrtf(x*x + y*y);
	}

	float Vector2D::LengthSquared()
	{
		return x*x + y*y;
	}

	float Vector2D::Dot(const Vector2D & right)
	{
		return (this->x * right.x) + (this->y * right.y);
	}

	Vector2D Vector2D::Normalize()
	{
		Vector2D newVec(this->x, this->y);
		float length = this->Length();
		newVec.x /= length;
		newVec.y /= length;
		return newVec;
	}

	Vector2D Vector2D::operator+(const Vector2D & right)
	{
		return Vector2D(x + right.x, y + right.y);
	}

	Vector2D Vector2D::operator-(const Vector2D & right)
	{
		return Vector2D(x - right.x, y - right.y);
	}

	Vector2D Vector2D::operator+(float s)
	{
		return Vector2D(x + s,y + s);
	}

	Vector2D Vector2D::operator-(float s)
	{
		return Vector2D(x - s, y - s);
	}

	Vector2D Vector2D::operator*(float s)
	{
		return Vector2D(x * s, y * s);
	}

	Vector2D Vector2D::operator/(float s)
	{
		return Vector2D(x / s, y / s);
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

	bool Vector2D::operator==(const Vector2D & right)
	{
		return (this->x == right.x && this->y == right.y);
	}

}