#include "matrix4d.h"
#include "math.h"
#include <math.h>

namespace SE3D
{
	Matrix4D::Matrix4D()
	{
		for (int16 i = 0; i < 16; i++)
		{
			this->elements[i] = 0;
		}
		this->elements[0] = 1;
		this->elements[4 * 1 + 1] = 1;
		this->elements[4 * 2 + 2] = 1;
		this->elements[4 * 3 + 3] = 1;
	}

	Matrix4D::Matrix4D(const Vector4D& column0, const Vector4D& column1, const Vector4D& column2, const Vector4D& column3)
	{
		this->columns[0] = column0;
		this->columns[1] = column1;
		this->columns[2] = column2;
		this->columns[3] = column3;
	}

	Matrix4D::Matrix4D(const Matrix3D& mat)
	{
		this->columns[0] = Vector4D(mat.GetColumn(0),0);
		this->columns[1] = Vector4D(mat.GetColumn(1),0);
		this->columns[2] = Vector4D(mat.GetColumn(2),0);
		this->columns[3] = Vector4D(mat.GetColumn(3),1);
	}

	Matrix4D Matrix4D::Orthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane)
	{
		Matrix4D ortho = Matrix4D::Identity();

		ortho.elements[0] = 2.0f / (right - left);
		ortho.elements[5] = 2.0f / (top - bottom);
		ortho.elements[12] = -(right + left) / (right - left);
		ortho.elements[13] = -(top + bottom) / (top - bottom);
		ortho.elements[10] = 2.0f / (farPlane - nearPlane);
		ortho.elements[14] = -(farPlane + nearPlane) / (farPlane - nearPlane);

		return ortho;
	}

	Matrix4D Matrix4D::Perspective(float fov, float aspectRatio, float nearPlane, float farPlane)
	{
		Matrix4D persp = {};

		float thv = static_cast<float>( tan(ToRadians(fov) / 2.0f) );

		persp.elements[0] = 1.0f / (aspectRatio * thv);
		persp.elements[5] = 1.0f / thv;
		persp.elements[11] = -1.0f;
		persp.elements[10] = -(farPlane + nearPlane) / (farPlane - nearPlane);
		persp.elements[14] = -(2.0f * farPlane * nearPlane) / (farPlane - nearPlane);

		return persp;
	}

	Matrix4D Matrix4D::LookAt(const Vector3D& position, const Vector3D& target, const Vector3D& up)
	{
		Matrix4D lookAt = Matrix4D::Identity();
		Vector3D f((target - position).Normalize());
		Vector3D s(f.Cross(up).Normalize());
		Vector3D u(s.Cross(f));
		
		lookAt.elements[0] = s.x;
		lookAt.elements[4] = s.y;
		lookAt.elements[8] = s.z;
		lookAt.elements[1] = u.x;
		lookAt.elements[5] = u.y;
		lookAt.elements[9] = u.z;
		lookAt.elements[2] = -f.x;
		lookAt.elements[6] = -f.y;
		lookAt.elements[10] = -f.z;
		lookAt.elements[12] = s.Dot(position) * -1;
		lookAt.elements[13] = u.Dot(position) * -1;
		lookAt.elements[14] = f.Dot(position);

		return lookAt;
	}

	Matrix4D Matrix4D::Identity()
	{
		Matrix4D identity;
		identity.elements[0] = 1;
		identity.elements[4 * 1 + 1] = 1;
		identity.elements[4 * 2 + 2] = 1;
		identity.elements[4 * 3 + 3] = 1;
		return identity;
	}

	Matrix4D Matrix4D::Transpose(const Matrix4D& matrix)
	{
		return Matrix4D(Vector4D(matrix.columns[0].x, matrix.columns[1].x, matrix.columns[2].x, matrix.columns[3].x),
		                Vector4D(matrix.columns[0].y, matrix.columns[1].y, matrix.columns[2].y, matrix.columns[3].y),
		                Vector4D(matrix.columns[0].z, matrix.columns[1].z, matrix.columns[2].z, matrix.columns[3].z),
		                Vector4D(matrix.columns[0].w, matrix.columns[1].w, matrix.columns[2].w, matrix.columns[3].w));
	}

	Matrix4D Matrix4D::TranslateMatrix(const Vector3D& translation)
	{
		Matrix4D translate = Matrix4D::Identity();

		translate.elements[12] = translation.x;
		translate.elements[13] = translation.y;
		translate.elements[14] = translation.z;

		return translate;
	}

	Matrix4D Matrix4D::RotateMatrix(const Vector3D& axis, float angle)
	{
		Matrix4D rotate = Matrix4D::Identity();

		float r = ToRadians(angle);
		float c = static_cast<float>(cos(r));
		float s = static_cast<float>(sin(r));

		rotate.elements[0] = axis.x * axis.x * 1.0f - c + c;
		rotate.elements[1] = axis.y * axis.x * 1.0f - c + axis.z * s;
		rotate.elements[2] = axis.x * axis.z * 1.0f - c - axis.y * s;
		rotate.elements[4] = axis.x * axis.y * 1.0f - c - axis.z * s;
		rotate.elements[5] = axis.y * axis.y * 1.0f - c + c;
		rotate.elements[6] = axis.y * axis.z * 1.0f - c + axis.x * s;
		rotate.elements[8] = axis.x * axis.z * 1.0f - c + axis.y * s;
		rotate.elements[9] = axis.y * axis.z * 1.0f - c - axis.x * s;
		rotate.elements[10] = axis.z * axis.z * 1.0f - c + c;

		return rotate;
	}

	Matrix4D Matrix4D::ScaleMatrix(const Vector3D& scale)
	{
		Matrix4D s;

		s.elements[0] = scale.x;
		s.elements[5] = scale.y;
		s.elements[10] = scale.z;

		return s;
	}

	Matrix4D& Matrix4D::Transpose()
	{
		*this = Matrix4D::Transpose(*this);
		return *this;
	}

	Matrix4D& Matrix4D::Add(const Matrix4D& matrix)
	{
		*this += matrix;
		return *this;
	}

	Matrix4D& Matrix4D::Subtract(const Matrix4D& matrix)
	{
		*this -= matrix;
		return *this;
	}

	Matrix4D& Matrix4D::Multiply(const Matrix4D& matrix)
	{
		*this *= matrix;
		return *this;
	}

	Matrix4D Matrix4D::Translate(const Vector3D& translation) const
	{
		return *this * TranslateMatrix(translation);
	}

	Matrix4D Matrix4D::Rotate(const Vector3D& axis, float angle) const
	{
		return *this * RotateMatrix(axis, angle);
	}

	Matrix4D Matrix4D::Scale(const Vector3D& scale) const
	{
		return *this * ScaleMatrix(scale);
	}

	Matrix4D Matrix4D::operator*(const Matrix4D& right) const
	{
		Matrix4D result;
		for (int32 row = 0; row < 4; row++)
		{
			for (int32 col = 0; col < 4; col++)
			{
				float sum = 0.0f;
				for (int32 el = 0; el < 4; el++)
				{
					sum += this->elements[el + row * 4] * right.elements[col + el * 4];
				}
				result.elements[col + row * 4] = sum;
			}
		}

		return result;
	}

	Matrix4D Matrix4D::operator+(float s) const
	{
		Matrix4D result;
		for (int32 row = 0; row < 4; row++)
		{
			for (int32 col = 0; col < 4; col++)
			{
				result.elements[col + row * 4] = this->elements[col + row * 4] + s;
			}
		}
		return result;
	}

	Matrix4D Matrix4D::operator-(float s) const
	{
		Matrix4D result;
		for (int32 row = 0; row < 4; row++)
		{
			for (int32 col = 0; col < 4; col++)
			{
				result.elements[col + row * 4] = this->elements[col + row * 4] - s;
			}
		}
		return result;
	}

	Matrix4D Matrix4D::operator*(float s) const
	{
		Matrix4D result;
		for (int32 row = 0; row < 4; row++)
		{
			for (int32 col = 0; col < 4; col++)
			{
				result.elements[col + row * 4] = this->elements[col + row * 4] * s;
			}
		}
		return result;
	}

	Vector4D Matrix4D::operator*(const Vector4D& right) const
	{
		return Vector4D(this->GetColumn(0).x * right.x + this->GetColumn(0).y * right.y + this->GetColumn(0).z * right.z + this->GetColumn(0).w * right.w,
		                this->GetColumn(1).x * right.x + this->GetColumn(1).y * right.y + this->GetColumn(1).z * right.z + this->GetColumn(1).w * right.w,
		                this->GetColumn(2).x * right.x + this->GetColumn(2).y * right.y + this->GetColumn(2).z * right.z + this->GetColumn(2).w * right.w,
		                this->GetColumn(3).x * right.x + this->GetColumn(3).y * right.y + this->GetColumn(3).z * right.z + this->GetColumn(3).w * right.w);
	}

	Matrix4D Matrix4D::operator+(const Matrix4D& right) const
	{
		Matrix4D result;

		for (int32 row = 0; row < 4; row++)
		{
			result.columns[row] = this->columns[row] + right.columns[row];
		}

		return result;
	}

	Matrix4D Matrix4D::operator-(const Matrix4D& right) const
	{
		Matrix4D result;

		for (int32 row = 0; row < 4; row++)
		{
			result.columns[row] = this->columns[row] - right.columns[row];
		}

		return result;
	}

	Matrix4D& Matrix4D::operator*=(const Matrix4D& right)
	{
		Matrix4D tmp = *this;
		for (int32 row = 0; row < 4; row++)
		{
			for (int32 col = 0; col < 4; col++)
			{
				float sum = 0.0f;
				for (int32 el = 0; el < 4; el++)
				{
					sum += tmp.elements[el + row * 4] * right.elements[col + el * 4];
				}
				this->elements[col + row * 4] = sum;
			}
		}

		return *this;
	}

	Matrix4D& Matrix4D::operator+=(float s)
	{
		for (int32 row = 0; row < 4; row++)
		{
			for (int32 col = 0; col < 4; col++)
			{
				this->elements[col + row * 4] += s;
			}
		}
		return *this;
	}

	Matrix4D& Matrix4D::operator-=(float s)
	{
		for (int32 row = 0; row < 4; row++)
		{
			for (int32 col = 0; col < 4; col++)
			{
				this->elements[col + row * 4] -= s;
			}
		}
		return *this;
	}

	Matrix4D& Matrix4D::operator*=(float s)
	{
		for (int32 row = 0; row < 4; row++)
		{
			for (int32 col = 0; col < 4; col++)
			{
				this->elements[col + row * 4] *= s;
			}
		}
		return *this;
	}

	Matrix4D& Matrix4D::operator+=(const Matrix4D& right)
	{
		for (int32 row = 0; row < 4; row++)
		{
			this->columns[row] += right.columns[row];
		}
		return *this;
	}

	Matrix4D& Matrix4D::operator-=(const Matrix4D& right)
	{
		for (int32 row = 0; row < 4; row++)
		{
			this->columns[row] -= right.columns[row];
		}
		return *this;
	}

	bool Matrix4D::operator==(const Matrix4D& right)
	{
		for (int32 row = 0; row < 4; row++)
		{
			if (!(this->columns[row] == right.columns[row]))
			{
				return false;
			}
		}
		return true;
	}

	bool Matrix4D::operator!=(const Matrix4D& right)
	{
		return !(*this == right);
	}
}
