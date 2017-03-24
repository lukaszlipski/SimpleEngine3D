#pragma once

#include "../utilities/types.h"
#include "vector3d.h"

namespace SE3D
{
	struct Matrix3D
	{
	private:
		union
		{
			float elements[3 * 3];
			Vector3D columns[3];
		};

	public:
		Matrix3D();
		Matrix3D(const Vector3D& column0, const Vector3D& column1, const Vector3D& column2);

		static Matrix3D Identity();
		static Matrix3D Transpose(const Matrix3D& matrix);
		static Matrix3D Invert(const Matrix3D& matrix);
		static Matrix3D RotateMatrix(const Vector3D& axis, float angle);
		static Matrix3D ScaleMatrix(const Vector3D& scale);

		inline float GetElement(int32 index) const { return this->elements[index]; };
		inline Vector3D GetRow(int32 index) const { return Vector3D(this->elements[index], this->elements[index + 3], this->elements[index + 6]); }
		inline Vector3D GetColumn(int32 index) const { return columns[index]; }

		inline Matrix3D& SetRow(int32 index, Vector3D row)
		{
			elements[index] = row.x;
			elements[index + 3] = row.y;
			elements[index + 6] = row.z;
			return *this;
		}

		inline Matrix3D& SetColumn(int32 index, Vector3D col)
		{
			columns[index] = col;
			return *this;
		}

		const void* GetPtr() const { return this; }

		Matrix3D& Transpose();
		Matrix3D& Invert();
		Matrix3D& Add(const Matrix3D& matrix);
		Matrix3D& Subtract(const Matrix3D& matrix);
		Matrix3D& Multiply(const Matrix3D& matrix);

		Matrix3D Rotate(const Vector3D& axis, float angle) const;
		Matrix3D Scale(const Vector3D& scale) const;

		Matrix3D operator+(const Matrix3D& right) const;
		Matrix3D operator-(const Matrix3D& right) const;
		Matrix3D operator*(const Matrix3D& right) const;

		Matrix3D operator+(float s) const;
		Matrix3D operator-(float s) const;
		Matrix3D operator*(float s) const;

		Vector3D operator*(const Vector3D& right) const;

		Matrix3D& operator+=(const Matrix3D& right);
		Matrix3D& operator-=(const Matrix3D& right);
		Matrix3D& operator*=(const Matrix3D& right);

		Matrix3D& operator+=(float s);
		Matrix3D& operator-=(float s);
		Matrix3D& operator*=(float s);

		bool operator==(const Matrix3D& right);
		bool operator!=(const Matrix3D& right);
	};
}
