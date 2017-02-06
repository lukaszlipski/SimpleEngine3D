#include "vector3d.h"
#include "matrix3d.h"
#include <math.h>

namespace SE3D
{
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

	float Vector3D::Length() const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	float Vector3D::LengthSquared() const
	{
		return x * x + y * y + z * z;
	}

	float Vector3D::Dot(const Vector3D& right) const
	{
		return (this->x * right.x) + (this->y * right.y) + (this->z * right.z);
	}

	Vector3D Vector3D::Normalize() const
	{
		Vector3D newVec(this->x, this->y, this->z);
		float length = this->Length();
		newVec.x /= length;
		newVec.y /= length;
		newVec.z /= length;
		return newVec;
	}

	Vector3D Vector3D::Cross(const Vector3D& right) const
	{
		return Vector3D(this->y * right.z - this->z * right.y, this->z * right.x - this->x * right.z, this->x * right.y - this->y * right.x);
	}

	Vector3D Vector3D::Transform(const Matrix3D& right) const
	{
		return right * *this;
	}

	Vector3D Vector3D::operator+(const Vector3D& right) const
	{
		return Vector3D(this->x + right.x, this->y + right.y, this->z + right.z);
	}

	Vector3D Vector3D::operator-(const Vector3D& right) const
	{
		return Vector3D(this->x - right.x, this->y - right.y, this->z - right.z);
	}

	Vector3D Vector3D::operator+(float s) const
	{
		return Vector3D(this->x + s, this->y + s, this->z + s);
	}

	Vector3D Vector3D::operator-(float s) const
	{
		return Vector3D(this->x - s, this->y - s, this->z - s);
	}

	Vector3D Vector3D::operator*(float s) const
	{
		return Vector3D(this->x * s, this->y * s, this->z * s);
	}

	Vector3D Vector3D::operator/(float s) const
	{
		return Vector3D(this->x / s, this->y / s, this->z / s);
	}

	Vector3D Vector3D::operator*(const Matrix3D& right) const
	{
		return Vector3D(right.GetColumn(0).x * this->x + right.GetColumn(0).y * this->y + right.GetColumn(0).z * this->z,
		                right.GetColumn(1).x * this->x + right.GetColumn(1).y * this->y + right.GetColumn(1).z * this->z,
		                right.GetColumn(2).x * this->x + right.GetColumn(2).y * this->y + right.GetColumn(2).z * this->z);
	}

	Vector3D& Vector3D::operator+=(const Vector3D& right)
	{
		this->x += right.x;
		this->y += right.y;
		this->z += right.z;
		return *this;
	}

	Vector3D& Vector3D::operator-=(const Vector3D& right)
	{
		this->x -= right.x;
		this->y -= right.y;
		this->z -= right.z;
		return *this;
	}

	Vector3D& Vector3D::operator+=(float s)
	{
		this->x += s;
		this->y += s;
		this->z += s;
		return *this;
	}

	Vector3D& Vector3D::operator-=(float s)
	{
		this->x -= s;
		this->y -= s;
		this->z -= s;
		return *this;
	}

	Vector3D& Vector3D::operator*=(float s)
	{
		this->x *= s;
		this->y *= s;
		this->z *= s;
		return *this;
	}

	Vector3D& Vector3D::operator/=(float s)
	{
		this->x /= s;
		this->y /= s;
		this->z /= s;
		return *this;
	}

	Vector3D& Vector3D::operator*=(const Matrix3D& right)
	{
		float x = right.GetColumn(0).x * this->x + right.GetColumn(0).y * this->y + right.GetColumn(0).z * this->z;
		float y = right.GetColumn(1).x * this->x + right.GetColumn(1).y * this->y + right.GetColumn(1).z * this->z;
		float z = right.GetColumn(2).x * this->x + right.GetColumn(2).y * this->y + right.GetColumn(2).z * this->z;

		this->x = x;
		this->y = y;
		this->z = z;

		return *this;
	}

	bool operator==(Vector3D left, const Vector3D& right)
	{
		return (left.x == right.x && left.y == right.y && left.z == right.z);
	}

	bool operator!=(Vector3D left, const Vector3D& right)
	{
		return !(left == right);
	}
}
