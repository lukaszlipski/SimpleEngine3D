#include "vector3d.h"
#include <math.h>

namespace SE3D {

	Vector3D::Vector3D()
		: x(0), y(0), z(0)
	{
	}

	Vector3D::Vector3D(float a, float b, float c)
		: x(a), y(b), z(c)
	{
	}

	Vector3D::Vector3D(Vector2D ab, float c)
		: x(ab.x), y(ab.y), z(c)
	{
	}

	float Vector3D::Length()
	{
		return sqrtf(x*x + y*y + z*z);
	}

	float Vector3D::LengthSquared()
	{
		return x*x + y*y + z*z;
	}

	float Vector3D::Dot(const Vector3D & right)
	{
		return (this->x * right.x) + (this->y * right.y) + (this->z * right.z);
	}

	Vector3D Vector3D::Normalize()
	{
		Vector3D newVec(this->x, this->y, this->z);
		float length = this->Length();
		newVec.x /= length;
		newVec.y /= length;
		return newVec;
	}

	Vector3D Vector3D::Cross(const Vector3D & right)
	{
		return Vector3D(this->y*right.z - this->z*right.y,this->z*right.x-this->x*right.z,this->x*right.y-this->y*right.x);
	}

	Vector3D Vector3D::operator+(const Vector3D & right)
	{
		return Vector3D(x + right.x, y + right.y, z + right.z);
	}

	Vector3D Vector3D::operator-(const Vector3D & right)
	{
		return Vector3D(x - right.x, y - right.y,z - right.z);
	}

	Vector3D Vector3D::operator+(float s)
	{
		return Vector3D(x + s, y + s, z + s);
	}

	Vector3D Vector3D::operator-(float s)
	{
		return Vector3D(x - s, y - s, z - s);
	}

	Vector3D Vector3D::operator*(float s)
	{
		return Vector3D(x * s, y * s, z * s);
	}

	Vector3D Vector3D::operator/(float s)
	{
		return Vector3D(x / s, y / s, z / s);
	}

	Vector3D & Vector3D::operator+=(const Vector3D & right)
	{
		this->x += right.x;
		this->y += right.y;
		this->z += right.z;
		return *this;
	}

	Vector3D & Vector3D::operator-=(const Vector3D & right)
	{
		this->x -= right.x;
		this->y -= right.y;
		this->z -= right.z;
		return *this;
	}

	Vector3D & Vector3D::operator+=(float s)
	{
		this->x += s;
		this->y += s;
		this->z += s;
		return *this;
	}

	Vector3D & Vector3D::operator-=(float s)
	{
		this->x -= s;
		this->y -= s;
		this->z -= s;
		return *this;
	}

	Vector3D & Vector3D::operator*=(float s)
	{
		this->x *= s;
		this->y *= s;
		this->z *= s;
		return *this;
	}

	Vector3D & Vector3D::operator/=(float s)
	{
		this->x /= s;
		this->y /= s;
		this->z /= s;
		return *this;
	}

	bool Vector3D::operator==(const Vector3D & right)
	{
		return (this->x == right.x && this->y == right.y && this->z == right.z);
	}

}