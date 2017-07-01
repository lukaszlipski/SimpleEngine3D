#include "vector4d.h"
#include "matrix4d.h"

namespace SE3D
{
	Vector4D::Vector4D()
		: x(0), y(0), z(0), w(0)
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

	float Vector4D::Dot(const Vector4D& right) const
	{
		return (this->x * right.x) + (this->y * right.y) + (this->z * right.z) + (this->w * right.w);
	}

	Vector4D Vector4D::Transform(const Matrix4D& right) const
	{
		return right * *this;
	}

	Vector4D Vector4D::operator+(const Vector4D& right) const
	{
		return Vector4D(this->x + right.x, this->y + right.y, this->z + right.z, this->w + right.w);
	}

	Vector4D Vector4D::operator-(const Vector4D& right) const
	{
		return Vector4D(this->x - right.x, this->y - right.y, this->z - right.z, this->w - right.w);
	}

	Vector4D Vector4D::operator+(float s) const
	{
		return Vector4D(this->x + s, this->y + s, this->z + s, this->w + s);
	}

	Vector4D Vector4D::operator-(float s) const
	{
		return Vector4D(this->x - s, this->y - s, this->z - s, this->w - s);
	}

	Vector4D Vector4D::operator*(float s) const
	{
		return Vector4D(this->x * s, this->y * s, this->z * s, this->w * s);
	}

	Vector4D Vector4D::operator*(const Vector4D& right) const
	{
		return Vector4D(this->x * right.x, this->y * right.y, this->z * right.z, this->w * right.w);
	}

	Vector4D Vector4D::operator/(float s) const
	{
		return Vector4D(this->x / s, this->y / s, this->z / s, this->w / s);
	}

	Vector4D Vector4D::operator*(const Matrix4D& right) const
	{
		return Vector4D(right.GetColumn(0).x * this->x + right.GetColumn(0).y * this->y + right.GetColumn(0).z * this->z + right.GetColumn(0).w * this->w,
		                right.GetColumn(1).x * this->x + right.GetColumn(1).y * this->y + right.GetColumn(1).z * this->z + right.GetColumn(1).w * this->w,
		                right.GetColumn(2).x * this->x + right.GetColumn(2).y * this->y + right.GetColumn(2).z * this->z + right.GetColumn(2).w * this->w,
		                right.GetColumn(3).x * this->x + right.GetColumn(3).y * this->y + right.GetColumn(3).z * this->z + right.GetColumn(3).w * this->w);
	}

	Vector4D& Vector4D::operator+=(const Vector4D& right)
	{
		this->x += right.x;
		this->y += right.y;
		this->z += right.z;
		this->w += right.w;
		return *this;
	}

	Vector4D& Vector4D::operator-=(const Vector4D& right)
	{
		this->x -= right.x;
		this->y -= right.y;
		this->z -= right.z;
		this->w -= right.w;
		return *this;
	}

	Vector4D& Vector4D::operator+=(float s)
	{
		this->x += s;
		this->y += s;
		this->z += s;
		this->w += s;
		return *this;
	}

	Vector4D& Vector4D::operator-=(float s)
	{
		this->x -= s;
		this->y -= s;
		this->z -= s;
		this->w -= s;
		return *this;
	}

	Vector4D& Vector4D::operator*=(float s)
	{
		this->x *= s;
		this->y *= s;
		this->z *= s;
		this->w *= s;
		return *this;
	}

	Vector4D& Vector4D::operator/=(float s)
	{
		this->x /= s;
		this->y /= s;
		this->z /= s;
		this->w /= s;
		return *this;
	}

	Vector4D& Vector4D::operator*=(const Matrix4D& right)
	{
		float x = right.GetColumn(0).x * this->x + right.GetColumn(0).y * this->y + right.GetColumn(0).z * this->z + right.GetColumn(0).w * this->w;
		float y = right.GetColumn(1).x * this->x + right.GetColumn(1).y * this->y + right.GetColumn(1).z * this->z + right.GetColumn(1).w * this->w;
		float z = right.GetColumn(2).x * this->x + right.GetColumn(2).y * this->y + right.GetColumn(2).z * this->z + right.GetColumn(2).w * this->w;
		float w = right.GetColumn(3).x * this->x + right.GetColumn(3).y * this->y + right.GetColumn(3).z * this->z + right.GetColumn(3).w * this->w;

		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;

		return *this;
	}

	bool operator==(Vector4D left, const Vector4D& right)
	{
		return (left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w);
	}

	bool operator!=(Vector4D left, const Vector4D& right)
	{
		return !(left == right);
	}
}
