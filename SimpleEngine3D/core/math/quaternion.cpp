#include "quaternion.h"
#include <math.h>
#include "math.h"

namespace SE3D
{

	Quaternion::Quaternion()
		: x(0), y(0), z(0), w(1)
	{
	}

	Quaternion::Quaternion(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Quaternion::Quaternion(Vector3D axis, float angle)
	{
		angle = ToRadians(angle);
		float sha = static_cast<float>(sin(angle / 2));

		x = axis.x * sha;
		y = axis.y * sha;
		z = axis.z * sha;
		w = static_cast<float>(cos(angle / 2));
	}

	Quaternion::Quaternion(const Quaternion& quaternion)
	{
		x = quaternion.x;
		y = quaternion.y;
		z = quaternion.z;
		w = quaternion.w;
	}

	Matrix4D Quaternion::ToRotationMatrix() const
	{
		Quaternion n = this->Normalize();
		Matrix4D rotation;

		rotation.SetColumn(0,Vector4D(1 - 2 * n.y*n.y - 2 * n.z*n.z, 2 * n.x*n.y + 2 * n.z*n.w, 2 * n.x*n.z - 2 * n.y*n.w, 0));
		rotation.SetColumn(1, Vector4D(2 * n.x*n.y - 2 * n.z*n.w, 1 - 2 * n.x*n.x - 2 * n.z*n.z, 2 * n.y*n.z + 2 * n.x*n.w, 0));
		rotation.SetColumn(2, Vector4D(2 * n.x*n.z + 2 * n.y*n.w, 2 * n.y*n.z - 2 * n.x*n.w, 1 - 2 * n.x*n.x - 2 * n.y*n.y, 0));
		rotation.SetColumn(3, Vector4D(0.0f, 0.0f, 0.0f, 1.0f));

		return rotation;
	}

	Vector3D Quaternion::GetRight() const
	{
		Quaternion right = *this * Vector3D(1, 0, 0) * this->Conjugate();
		return Vector3D(right.x,right.y,right.z);
	}

	Vector3D Quaternion::GetForward() const
	{
		Quaternion right = *this * Vector3D(0, 0, -1) * this->Conjugate();
		return Vector3D(right.x, right.y, right.z);
	}

	Quaternion& Quaternion::operator+=(const Quaternion& right) 
	{
		this->x += right.x;
		this->y += right.y;
		this->z += right.z;
		this->w += right.w;

		return *this;
	}

	Quaternion& Quaternion::operator-=(const Quaternion& right) 
	{
		this->x -= right.x;
		this->y -= right.y;
		this->z -= right.z;
		this->w -= right.w;

		return *this;
	}

	Quaternion& Quaternion::operator*=(const Quaternion& right) 
	{
		float w = this->w * right.w - this->x * right.x - this->y * right.y - this->z * right.z;
		float x = this->x * right.w + this->w * right.x + this->y * right.z - this->z * right.y;
		float y = this->y * right.w + this->w * right.y + this->z * right.x - this->x * right.z;
		float z = this->z * right.w + this->w * right.z + this->x * right.y - this->y * right.x;

		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;

		return *this;
	}

	Quaternion& Quaternion::operator*=(const Vector3D& right) 
	{
		float w = -this->x * right.x - this->y * right.y - this->z * right.z;
		float x = this->w * right.x + this->y * right.z - this->z * right.y;
		float y = this->w * right.y + this->z * right.x - this->x * right.z;
		float z = this->w * right.z + this->x * right.y - this->y * right.x;

		this->w = w;
		this->x = x;
		this->y = y;
		this->z = z;

		return *this;
	}

	Quaternion& Quaternion::operator*=(float s) 
	{
		this->x *= s;
		this->y *= s;
		this->z *= s;
		this->w *= s;

		return *this;
	}

	Quaternion& Quaternion::operator/=(float s) 
	{
		this->x /= s;
		this->y /= s;
		this->z /= s;
		this->w /= s;

		return *this;
	}

	float Quaternion::Length() const
	{
		return static_cast<float>(sqrt(x*x + y*y + z*z + w*w));
	}

	Quaternion Quaternion::Normalize() const
	{
		float length = Length();
		return Quaternion(x / length, y / length, z / length, w / length);
	}

	Quaternion Quaternion::Conjugate() const
	{
		return Quaternion(-x, -y, -z, w);
	}

	Quaternion operator+(Quaternion left, const Quaternion& right) 
	{
		return Quaternion(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
	}

	Quaternion operator-(Quaternion left, const Quaternion& right) 
	{
		return Quaternion(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
	}

	Quaternion operator*(Quaternion left, const Quaternion& right) 
	{
		float w = left.w * right.w - left.x * right.x - left.y * right.y - left.z * right.z;
		float x = left.x * right.w + left.w * right.x + left.y * right.z - left.z * right.y;
		float y = left.y * right.w + left.w * right.y + left.z * right.x - left.x * right.z;
		float z = left.z * right.w + left.w * right.z + left.x * right.y - left.y * right.x;

		return Quaternion(x, y, z, w);
	}

	Quaternion operator*(Quaternion left, const Vector3D& right) 
	{
		left *= right;
		return left;
	}

	Quaternion operator*(Quaternion left, float s) 
	{
		return Quaternion(left.x * s, left.y * s, left.z * s, left.w * s);
	}

	Quaternion operator/(Quaternion left, float s) 
	{
		return Quaternion(left.x / s, left.y / s, left.z / s, left.w / s);
	}

	bool operator==(Quaternion left, const Quaternion& right) 
	{
		return (left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w);
	}

	bool operator!=(Quaternion left, const Quaternion& right) 
	{
		return !(left == right);
	}
}
