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

		ortho.elements[0] = 2.0f / (right - left);
		ortho.elements[5] = 2.0f / (top - bottom);
		ortho.elements[10] = 2.0f / (nearPlane - farPlane);
		ortho.elements[3] = (left + right) / (left - right);
		ortho.elements[7] = (bottom + top) / (bottom - top);
		ortho.elements[11] = (farPlane + nearPlane) / (farPlane - nearPlane);

		return ortho;
	}

	Matrix4D Matrix4D::Perspective(float fov, float aspectRatio, float nearPlane, float farPlane)
	{
		Matrix4D persp = Matrix4D::Identity();

		float q = 1.0f / static_cast<float>(tan(ToRadians(0.5f * fov)));
		float a = q / aspectRatio;

		float b = (nearPlane + farPlane) / (nearPlane - farPlane);
		float c = (2.0f * nearPlane * farPlane) / (nearPlane - farPlane);

		persp.elements[0] = a;
		persp.elements[5] = q;
		persp.elements[10] = b;
		persp.elements[14] = -1.0f;
		persp.elements[11] = c;

		return persp;
	}

	Matrix4D Matrix4D::LookAt(const Vector3D& position, const Vector3D& target, const Vector3D& up)
	{
		Matrix4D lookAt = Matrix4D::Identity();
		Vector3D f = (target - position).Normalize();
		Vector3D s = f.Cross(up.Normalize());
		Vector3D u = s.Cross(f);

		lookAt.elements[0] = s.x;
		lookAt.elements[4] = s.y;
		lookAt.elements[8] = s.z;
		lookAt.elements[1] = u.x;
		lookAt.elements[5] = u.y;
		lookAt.elements[9] = u.z;
		lookAt.elements[2] = -f.x;
		lookAt.elements[6] = -f.y;
		lookAt.elements[10] = -f.z;

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

	Matrix4D Matrix4D::Translate(const Vector3D& translation)
	{
		Matrix4D translate = Matrix4D::Identity();

		translate.elements[3] = translation.x;
		translate.elements[3 + 4] = translation.y;
		translate.elements[3 + 8] = translation.z;

		return translate;
	}

	Matrix4D Matrix4D::Rotate(float angle, const Vector3D& axis)
	{
		Matrix4D rotate;

		float r = ToRadians(angle);
		float c = static_cast<float>(cos(r));
		float s = static_cast<float>(sin(r));
		float omc = 1.0f - c;

		float x = axis.x;
		float y = axis.y;
		float z = axis.z;

		rotate.elements[0] = x * x * omc + c;
		rotate.elements[4] = y * x * omc + z * s;
		rotate.elements[8] = x * z * omc - y * s;
		rotate.elements[1] = x * y * omc - z * s;
		rotate.elements[5] = y * y * omc + c;
		rotate.elements[9] = y * z * omc + x * s;
		rotate.elements[2] = x * z * omc + y * s;
		rotate.elements[6] = y * z * omc - x * s;
		rotate.elements[10] = z * z * omc + c;

		return rotate;
	}

	Matrix4D Matrix4D::Scale(const Vector3D& scale)
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
