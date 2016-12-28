#include "matrix3d.h"
#include "../utilities/assertion.h"
#include "math.h"
#include <math.h>

namespace SE3D
{
	Matrix3D::Matrix3D()
	{
		for (int16 i = 0; i < 9; i++)
		{
			this->elements[i] = 0;
		}
		this->elements[0] = 1;
		this->elements[3 * 1 + 1] = 1;
		this->elements[3 * 2 + 2] = 1;
	}

	Matrix3D::Matrix3D(const Vector3D& row1, const Vector3D& row2, const Vector3D& row3)
	{
		this->rows[0] = row1;
		this->rows[1] = row2;
		this->rows[2] = row3;
	}

	Matrix3D Matrix3D::Identity()
	{
		Matrix3D identity;
		identity.elements[0] = 1;
		identity.elements[3 * 1 + 1] = 1;
		identity.elements[3 * 2 + 2] = 1;
		return identity;
	}

	Matrix3D Matrix3D::Transpose(const Matrix3D& matrix)
	{
		return Matrix3D(Vector3D(matrix.rows[0].x, matrix.rows[1].x, matrix.rows[2].x),
		                Vector3D(matrix.rows[0].y, matrix.rows[1].y, matrix.rows[2].y),
		                Vector3D(matrix.rows[0].z, matrix.rows[1].z, matrix.rows[2].z));
	}

	Matrix3D Matrix3D::Invert(const Matrix3D& matrix)
	{
		Matrix3D invert;

		invert.elements[0] = matrix.rows[1].y * matrix.rows[2].z - matrix.rows[1].z * matrix.rows[2].y;
		invert.elements[1] = -(matrix.rows[1].x * matrix.rows[2].z - matrix.rows[1].z * matrix.rows[2].x);
		invert.elements[2] = matrix.rows[1].x * matrix.rows[2].y - matrix.rows[1].y * matrix.rows[2].x;
		invert.elements[3] = -(matrix.rows[0].y * matrix.rows[2].z - matrix.rows[0].z * matrix.rows[2].y);
		invert.elements[4] = matrix.rows[0].x * matrix.rows[2].z - matrix.rows[0].z * matrix.rows[2].x;
		invert.elements[5] = -(matrix.rows[0].x * matrix.rows[2].y - matrix.rows[0].y * matrix.rows[2].x);
		invert.elements[6] = matrix.rows[0].y * matrix.rows[1].z - matrix.rows[0].z * matrix.rows[1].y;
		invert.elements[7] = -(matrix.rows[0].x * matrix.rows[1].z - matrix.rows[0].z * matrix.rows[1].x);
		invert.elements[8] = matrix.rows[0].x * matrix.rows[1].y - matrix.rows[0].y * matrix.rows[1].x;

		float det = matrix.rows[0].x * invert.elements[0] + matrix.rows[0].y * invert.elements[1] + matrix.rows[0].z * invert.elements[2];
		Assert(det != 0);

		return Matrix3D::Transpose(invert) * (1 / det);
	}

	Matrix3D Matrix3D::Rotate(float angle, const Vector3D& axis)
	{
		Matrix3D rotate;

		float r = ToRadians(angle);
		float c = static_cast<float>(cos(r));
		float s = static_cast<float>(sin(r));
		float omc = 1.0f - c;

		float x = axis.x;
		float y = axis.y;
		float z = axis.z;

		rotate.elements[0] = x * x * omc + c;
		rotate.elements[3] = y * x * omc + z * s;
		rotate.elements[6] = x * z * omc - y * s;
		rotate.elements[1] = x * y * omc - z * s;
		rotate.elements[4] = y * y * omc + c;
		rotate.elements[7] = y * z * omc + x * s;
		rotate.elements[2] = x * z * omc + y * s;
		rotate.elements[5] = y * z * omc - x * s;
		rotate.elements[8] = z * z * omc + c;

		return rotate;
	}

	Matrix3D Matrix3D::Scale(const Vector3D& scale)
	{
		Matrix3D s;

		s.elements[0] = scale.x;
		s.elements[4] = scale.y;
		s.elements[8] = scale.z;

		return s;
	}

	Matrix3D& Matrix3D::Transpose()
	{
		*this = Matrix3D::Transpose(*this);
		return *this;
	}

	Matrix3D& Matrix3D::Invert()
	{
		*this = Matrix3D::Invert(*this);
		return *this;
	}

	Matrix3D& Matrix3D::Add(const Matrix3D& matrix)
	{
		*this += matrix;
		return *this;
	}

	Matrix3D& Matrix3D::Subtract(const Matrix3D& matrix)
	{
		*this -= matrix;
		return *this;
	}

	Matrix3D& Matrix3D::Multiply(const Matrix3D& matrix)
	{
		*this *= matrix;
		return *this;
	}

	Matrix3D Matrix3D::operator+(const Matrix3D& right) const
	{
		Matrix3D result;

		for (int32 row = 0; row < 3; row++)
		{
			result.rows[row] = this->rows[row] + right.rows[row];
		}

		return result;
	}

	Matrix3D Matrix3D::operator-(const Matrix3D& right) const
	{
		Matrix3D result;

		for (int32 row = 0; row < 3; row++)
		{
			result.rows[row] = this->rows[row] - right.rows[row];
		}

		return result;
	}

	Matrix3D Matrix3D::operator*(const Matrix3D& right) const
	{
		Matrix3D result;
		for (int32 row = 0; row < 3; row++)
		{
			for (int32 col = 0; col < 3; col++)
			{
				float sum = 0.0f;
				for (int32 el = 0; el < 3; el++)
				{
					sum += this->elements[el + row * 3] * right.elements[col + el * 3];
				}
				result.elements[col + row * 3] = sum;
			}
		}

		return result;
	}

	Matrix3D Matrix3D::operator+(float s) const
	{
		Matrix3D result;
		for (int32 row = 0; row < 3; row++)
		{
			for (int32 col = 0; col < 3; col++)
			{
				result.elements[col + row * 3] = this->elements[col + row * 3] + s;
			}
		}
		return result;
	}

	Matrix3D Matrix3D::operator-(float s) const
	{
		Matrix3D result;
		for (int32 row = 0; row < 3; row++)
		{
			for (int32 col = 0; col < 3; col++)
			{
				result.elements[col + row * 3] = this->elements[col + row * 3] - s;
			}
		}
		return result;
	}

	Matrix3D Matrix3D::operator*(float s) const
	{
		Matrix3D result;
		for (int32 row = 0; row < 3; row++)
		{
			for (int32 col = 0; col < 3; col++)
			{
				result.elements[col + row * 3] = this->elements[col + row * 3] * s;
			}
		}
		return result;
	}

	Vector3D Matrix3D::operator*(const Vector3D& right) const
	{
		return Vector3D(this->GetRow(0).x * right.x + this->GetRow(0).y * right.y + this->GetRow(0).z * right.z,
		                this->GetRow(1).x * right.x + this->GetRow(1).y * right.y + this->GetRow(1).z * right.z,
		                this->GetRow(2).x * right.x + this->GetRow(2).y * right.y + this->GetRow(2).z * right.z);
	}

	Matrix3D& Matrix3D::operator+=(const Matrix3D& right)
	{
		for (int32 row = 0; row < 3; row++)
		{
			this->rows[row] += right.rows[row];
		}
		return *this;
	}

	Matrix3D& Matrix3D::operator-=(const Matrix3D& right)
	{
		for (int32 row = 0; row < 3; row++)
		{
			this->rows[row] -= right.rows[row];
		}
		return *this;
	}

	Matrix3D& Matrix3D::operator*=(const Matrix3D& right)
	{
		Matrix3D tmp = *this;
		for (int32 row = 0; row < 3; row++)
		{
			for (int32 col = 0; col < 3; col++)
			{
				float sum = 0.0f;
				for (int32 el = 0; el < 3; el++)
				{
					sum += tmp.elements[el + row * 3] * right.elements[col + el * 3];
				}
				this->elements[col + row * 3] = sum;
			}
		}

		return *this;
	}

	Matrix3D& Matrix3D::operator+=(float s)
	{
		for (int32 row = 0; row < 3; row++)
		{
			for (int32 col = 0; col < 3; col++)
			{
				this->elements[col + row * 3] += s;
			}
		}
		return *this;
	}

	Matrix3D& Matrix3D::operator-=(float s)
	{
		for (int32 row = 0; row < 3; row++)
		{
			for (int32 col = 0; col < 3; col++)
			{
				this->elements[col + row * 3] -= s;
			}
		}
		return *this;
	}

	Matrix3D& Matrix3D::operator*=(float s)
	{
		for (int32 row = 0; row < 3; row++)
		{
			for (int32 col = 0; col < 3; col++)
			{
				this->elements[col + row * 3] *= s;
			}
		}
		return *this;
	}

	bool Matrix3D::operator==(const Matrix3D& right)
	{
		for (int32 row = 0; row < 3; row++)
		{
			if (!(this->rows[row] == right.rows[row]))
			{
				return false;
			}
		}
		return true;
	}

	bool Matrix3D::operator!=(const Matrix3D& right)
	{
		return !(*this == right);
	}
}
