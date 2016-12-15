#include "vector4d.h"
#include <math.h>

namespace SE3D {

	Vector4D::Vector4D()
		: x(0), y(0), z(0)
	{
	}

	Vector4D::Vector4D(float a, float b, float c, float d)
		: x(a), y(b), z(c), w(d)
	{
	}

	Vector4D::Vector4D(Vector2D ab, float c, float d)
		: x(ab.x), y(ab.y), z(c), w(d)
	{
	}

	Vector4D::Vector4D(Vector3D abc, float d)
		: x(abc.x), y(abc.y), z(abc.z), w(d)
	{
	}

	float Vector4D::Dot(const Vector4D & right) const
	{
		return (this->x * right.x) + (this->y * right.y) + (this->z * right.z) + (this->w * right.w);
	}

	Vector4D operator+(Vector4D left, const Vector4D & right)
	{
		return Vector4D(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
	}

	Vector4D operator-(Vector4D left, const Vector4D & right)
	{
		return Vector4D(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
	}

	Vector4D operator+(Vector4D left, float s)
	{
		return Vector4D(left.x + s, left.y + s, left.z + s, left.w + s);
	}

	Vector4D operator-(Vector4D left, float s)
	{
		return Vector4D(left.x - s, left.y - s, left.z - s, left.w - s);
	}

	Vector4D operator*(Vector4D left, float s)
	{
		return Vector4D(left.x * s, left.y * s, left.z * s, left.w * s);
	}

	Vector4D operator/(Vector4D left, float s)
	{
		return Vector4D(left.x / s, left.y / s, left.z / s , left.w / s);
	}

	Vector4D & Vector4D::operator+=(const Vector4D & right)
	{
		this->x += right.x;
		this->y += right.y;
		this->z += right.z;
		this->w += right.w;
		return *this;
	}

	Vector4D & Vector4D::operator-=(const Vector4D & right)
	{
		this->x -= right.x;
		this->y -= right.y;
		this->z -= right.z;
		this->w -= right.w;
		return *this;
	}

	Vector4D & Vector4D::operator+=(float s)
	{
		this->x += s;
		this->y += s;
		this->z += s;
		this->w += s;
		return *this;
	}

	Vector4D & Vector4D::operator-=(float s)
	{
		this->x -= s;
		this->y -= s;
		this->z -= s;
		this->w -= s;
		return *this;
	}

	Vector4D & Vector4D::operator*=(float s)
	{
		this->x *= s;
		this->y *= s;
		this->z *= s;
		this->w *= s;
		return *this;
	}

	Vector4D & Vector4D::operator/=(float s)
	{
		this->x /= s;
		this->y /= s;
		this->z /= s;
		this->w /= s;
		return *this;
	}

	bool operator==(Vector4D left, const Vector4D & right)
	{
		return (left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w);
	}

	bool operator!=(Vector4D left, const Vector4D & right)
	{
		return !(left == right);
	}

}