#pragma once
#include "vector4d.h"
#include "../utilities/types.h"
#include "math.h"

namespace SE3D {

	struct Matrix4D{

	private:
		union
		{
			Vector4D rows[4];
			float elements[4 * 4];
		};

	public:
		Matrix4D();
		Matrix4D(const Vector4D& row1, const Vector4D& row2, const Vector4D& row3, const Vector4D& row4);

		static Matrix4D Orthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane);
		static Matrix4D Perspective(float fov, float aspectRatio, float nearPlane, float farPlane);
		static Matrix4D LookAt(const Vector3D& position, const Vector3D& target, const Vector3D& up);

		static Matrix4D Identity()
		{
			Matrix4D identity;
			identity.elements[0] = 1;
			identity.elements[4 * 1 + 1] = 1;
			identity.elements[4 * 2 + 2] = 1;
			identity.elements[4 * 3 + 3] = 1;
			return identity;
		}
		static Matrix4D Transpose(const Matrix4D& matrix);
		//static Matrix4D Invert(const Matrix4D& matrix);
		static Matrix4D Translate(const Vector3D& translation);
		static Matrix4D Rotate(float angle, const Vector3D& axis);
		static Matrix4D Scale(const Vector3D& scale);

		inline float GetElement(int32 index) const { return this->elements[index]; };
		inline Vector4D GetRow(int32 index) const { return this->rows[index]; }
		inline Vector4D GetColumn(int32 index) const { return Vector4D(this->elements[index], this->elements[index + 4], this->elements[index + 8], this->elements[index + 12]); }
		inline Vector3D GetPosition() const { return Vector3D(this->rows[0].w,this->rows[1].w,this->rows[2].w); }

		void Transpose();
		//void Invert();
		void Add(const Matrix4D& matrix);
		void Subtract(const Matrix4D& matrix);
		void Multiply(const Matrix4D& matrix);

		Matrix4D operator+(const Matrix4D& right);
		Matrix4D operator-(const Matrix4D& right);
		Matrix4D operator*(const Matrix4D& right);

		Matrix4D& operator+=(const Matrix4D& right);
		Matrix4D& operator-=(const Matrix4D& right);
		Matrix4D& operator*=(const Matrix4D& right);

		bool operator==(const Matrix4D& right);
		bool operator!=(const Matrix4D& right);

	};
}