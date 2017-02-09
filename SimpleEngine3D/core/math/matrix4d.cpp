#include "matrix4d.h"
#include "math.h"
#include <math.h>
#include <winerror.h>

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

	Matrix4D::Matrix4D(const Vector4D& row1, const Vector4D& row2, const Vector4D& row3, const Vector4D& row4)
	{
		this->rows[0] = row1;
		this->rows[1] = row2;
		this->rows[2] = row3;
		this->rows[3] = row4;
	}

	Matrix4D::Matrix4D(const Matrix3D& mat)
	{
		this->rows[0] = Vector4D(mat.GetRow(0), 0);
		this->rows[1] = Vector4D(mat.GetRow(1), 0);
		this->rows[2] = Vector4D(mat.GetRow(2), 0);
		this->rows[3] = Vector4D(0, 0, 0, 1);
	}

	Matrix4D Matrix4D::Orthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane)
	{
		Matrix4D ortho = Matrix4D::Identity();

		ortho.SetColumn(0, Vector4D(2.0f / (right - left), 0, 0, 0));
		ortho.SetColumn(1, Vector4D(0, 2.0f / (top - bottom), 0, 0));
		ortho.SetColumn(2, Vector4D(0, 0, -2.0f / (farPlane - nearPlane), 0));
		ortho.SetColumn(3, Vector4D(-(left + right) / (right - left), -(bottom + top) / (top - bottom), -(farPlane + nearPlane) / (farPlane - nearPlane), 1));

		return ortho;
	}

	Matrix4D Matrix4D::Perspective(float fov, float aspectRatio, float nearPlane, float farPlane)
	{
		Matrix4D persp = {};

		float tanHalfFov = static_cast<float>(tan(fov / 2.0f));

		persp.SetColumn(0, Vector4D(1.0f / (aspectRatio * tanHalfFov), 0, 0, 0));
		persp.SetColumn(1, Vector4D(0, 1.0f / tanHalfFov, 0, 0));
		persp.SetColumn(2, Vector4D(0, 0, -(farPlane + nearPlane) / (farPlane - nearPlane), -1));
		persp.SetColumn(3, Vector4D(0, 0, (-2.0f * farPlane * nearPlane) / (farPlane - nearPlane), 0));

		return persp;
	}

	Matrix4D Matrix4D::LookAt(const Vector3D& position, const Vector3D& target, const Vector3D& up)
	{
		Matrix4D lookAt = Matrix4D::Identity();
		Vector3D f = (target - position).Normalize();
		Vector3D s = f.Cross(up.Normalize());
		Vector3D u = s.Cross(f);

		lookAt.SetRow(0, Vector4D(s.x, s.y, s.z, -s.Dot(position)));
		lookAt.SetRow(1, Vector4D(u.x, u.y, u.z, -u.Dot(position)));
		lookAt.SetRow(2, Vector4D(-f.x, -f.y, -f.z, f.Dot(position)));
		lookAt.SetRow(3, Vector4D(0, 0, 0, 1));

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
		return Matrix4D(Vector4D(matrix.rows[0].x, matrix.rows[1].x, matrix.rows[2].x, matrix.rows[3].x),
		                Vector4D(matrix.rows[0].y, matrix.rows[1].y, matrix.rows[2].y, matrix.rows[3].y),
		                Vector4D(matrix.rows[0].z, matrix.rows[1].z, matrix.rows[2].z, matrix.rows[3].z),
		                Vector4D(matrix.rows[0].w, matrix.rows[1].w, matrix.rows[2].w, matrix.rows[3].w));
	}

	Matrix4D Matrix4D::TranslateMatrix(const Vector3D& translation)
	{
		Matrix4D translate = Matrix4D::Identity();

		translate.elements[3] = translation.x;
		translate.elements[3 + 4] = translation.y;
		translate.elements[3 + 8] = translation.z;

		return translate;
	}

	Matrix4D Matrix4D::RotateMatrix(float angle, const Vector3D& axis)
	{
		Matrix4D rotate = Matrix4D::Identity();

		float r = ToRadians(angle);
		float c = static_cast<float>(cos(r));
		float s = static_cast<float>(sin(r));
		float omc = 1.0f - c;

		float x = axis.x;
		float y = axis.y;
		float z = axis.z;

		rotate.SetRow(0, Vector4D(x * x * omc + c, y * x * omc + z * s, x * z * omc - y * s, 0));
		rotate.SetRow(1, Vector4D(x * y * omc - z * s, y * y * omc + c, y * z * omc + x * s, 0));
		rotate.SetRow(2, Vector4D(x * z * omc + y * s, y * z * omc - x * s, z * z * omc + c, 0));

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

	Matrix4D Matrix4D::Rotate(float angle, const Vector3D& axis) const
	{
		return *this * RotateMatrix(angle, axis);
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
		return Vector4D(this->GetRow(0).x * right.x + this->GetRow(0).y * right.y + this->GetRow(0).z * right.z + this->GetRow(0).w * right.w,
		                this->GetRow(1).x * right.x + this->GetRow(1).y * right.y + this->GetRow(1).z * right.z + this->GetRow(1).w * right.w,
		                this->GetRow(2).x * right.x + this->GetRow(2).y * right.y + this->GetRow(2).z * right.z + this->GetRow(2).w * right.w,
		                this->GetRow(3).x * right.x + this->GetRow(3).y * right.y + this->GetRow(3).z * right.z + this->GetRow(3).w * right.w);
	}

	Matrix4D Matrix4D::operator+(const Matrix4D& right) const
	{
		Matrix4D result;

		for (int32 row = 0; row < 4; row++)
		{
			result.rows[row] = this->rows[row] + right.rows[row];
		}

		return result;
	}

	Matrix4D Matrix4D::operator-(const Matrix4D& right) const
	{
		Matrix4D result;

		for (int32 row = 0; row < 4; row++)
		{
			result.rows[row] = this->rows[row] - right.rows[row];
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
			this->rows[row] += right.rows[row];
		}
		return *this;
	}

	Matrix4D& Matrix4D::operator-=(const Matrix4D& right)
	{
		for (int32 row = 0; row < 4; row++)
		{
			this->rows[row] -= right.rows[row];
		}
		return *this;
	}

	bool Matrix4D::operator==(const Matrix4D& right)
	{
		for (int32 row = 0; row < 4; row++)
		{
			if (!(this->rows[row] == right.rows[row]))
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
