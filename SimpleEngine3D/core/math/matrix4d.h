#pragma once

#include "../utilities/types.h"
#include "vector4d.h"
#include "matrix3d.h"
#include "../utilities/assertion.h"

namespace SE3D
{
	struct Matrix4D
	{
	private:
		union
		{
			float elements[4 * 4];
			Vector4D columns[4];
		};

	public:
		Matrix4D();
		Matrix4D(const Vector4D& column0, const Vector4D& column1, const Vector4D& column2, const Vector4D& column3);
		Matrix4D(const Matrix3D& mat);

		static Matrix4D Orthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane);
		static Matrix4D Perspective(float fov, float aspectRatio, float nearPlane, float farPlane);
		static Matrix4D LookAt(const Vector3D& position, const Vector3D& target, const Vector3D& up);

		static Matrix4D Identity();
		static Matrix4D Transpose(const Matrix4D& matrix);
		static Matrix4D Inverse(const Matrix4D& matrix);
		static Matrix4D TranslateMatrix(const Vector3D& translation);
		static Matrix4D RotateMatrix(const Vector3D& axis, float angle);
		static Matrix4D ScaleMatrix(const Vector3D& scale);

		inline float GetElement(int32 index) const { return this->elements[index]; };
		inline Vector4D GetRow(int32 index) const { return Vector4D(this->elements[index], this->elements[index + 4], this->elements[index + 8], this->elements[index + 12]); }
		inline Vector4D GetColumn(int32 index) const { return columns[index]; }
		inline Vector3D GetPosition() const { return Vector3D(this->columns[0].w, this->columns[1].w, this->columns[2].w); }

		inline Matrix4D& SetRow(int32 index, Vector4D row)
		{
			elements[index] = row.x;
			elements[index + 4] = row.y;
			elements[index + 8] = row.z;
			elements[index + 12] = row.w;
			return *this;
		}

		inline Matrix4D& SetColumn(int32 index, Vector4D col)
		{
			columns[index] = col;
			return *this;
		}

		const void* GetPtr() const { return this; }

		Matrix4D& Transpose();
		Matrix4D& Inverse();
		Matrix4D& Add(const Matrix4D& matrix);
		Matrix4D& Subtract(const Matrix4D& matrix);
		Matrix4D& Multiply(const Matrix4D& matrix);

		Matrix4D Translate(const Vector3D& translation) const;
		Matrix4D Rotate(const Vector3D& axis, float angle) const;
		Matrix4D Scale(const Vector3D& scale) const;

		Matrix4D operator+(const Matrix4D& right) const;
		Matrix4D operator-(const Matrix4D& right) const;
		Matrix4D operator*(const Matrix4D& right) const;

		Matrix4D operator+(float s) const;
		Matrix4D operator-(float s) const;
		Matrix4D operator*(float s) const;

		Vector4D operator*(const Vector4D& right) const;

		Matrix4D& operator+=(const Matrix4D& right);
		Matrix4D& operator-=(const Matrix4D& right);
		Matrix4D& operator*=(const Matrix4D& right);

		Matrix4D& operator+=(float s);
		Matrix4D& operator-=(float s);
		Matrix4D& operator*=(float s);

		bool operator==(const Matrix4D& right);
		bool operator!=(const Matrix4D& right);
	};
}
