//#include "Math.h"
//using namespace Matrix;

#include <iostream>
#include <memory.h>
#include "Matrix4.h"
#include "Vector3.h"
#include "Vector4.h"


Matrix4::Matrix4(float  m0, float  m1, float  m2, float  m3,
	float  m4, float  m5, float  m6, float  m7,
	float  m8, float  m9, float m10, float m11,
	float m12, float m13, float m14, float m15)
{
	m[0] = m0; m[1] = m1; m[2] = m2; m[3] = m3;
	m[4] = m4; m[5] = m5; m[6] = m6; m[7] = m7;
	m[8] = m8; m[9] = m9; m[10] = m10; m[11] = m11;
	m[12] = m12; m[13] = m13; m[14] = m14; m[15] = m15;
}

Matrix4::Matrix4(const Matrix4& old)
{
	memcpy(m, old.m, 16 * sizeof(float));
}

Matrix4::Matrix4(const float* old)
{
	memcpy(m, old, 16 * sizeof(float));
}

Vector4 Matrix4::GetRow(int rowIndex) const
{
	switch (rowIndex)
	{
	case 0:	return Vector4(m[0], m[4], m[8], m[12]); break;
	case 1:	return Vector4(m[1], m[5], m[9], m[13]); break;
	case 2:	return Vector4(m[2], m[6], m[10], m[14]); break;
	case 3:	return Vector4(m[3], m[7], m[11], m[15]); break;
	default: return Vector4(0.f, 0.f, 0.f, 0.f);
	}
}

Vector4 Matrix4::GetColumn(int cloumnIndex) const
{
	switch (cloumnIndex)
	{
	case 0:	return Vector4(m[0], m[1], m[2], m[3]); break;
	case 1:	return Vector4(m[4], m[5], m[6], m[7]); break;
	case 2:	return Vector4(m[8], m[9], m[10], m[11]); break;
	case 3:	return Vector4(m[12], m[13], m[14], m[15]); break;
	default:return Vector4(0.0f, 0.0f, 0.0f, 0.0f);
	}
}

void Matrix4::Identity()
{
	memset(m, 0, 16 * sizeof(float));
	m[0] = m[5] = m[10] = m[15] = 1.0f;
}

void Matrix4::Zero()
{
	memset(m, 0, 16 * sizeof(float));
}

void Matrix4::Print()
{
	std::cout << "[\t" << m[0 ] << "\t" << m[1 ] << "\t" << m[2 ] << "\t" << m[3 ] << "\t]" << std::endl;
	std::cout << "|\t" << m[4 ] << "\t" << m[5 ] << "\t" << m[6 ] << "\t" << m[7 ] << "\t|" << std::endl;
	std::cout << "|\t" << m[8 ] << "\t" << m[9 ] << "\t" << m[10] << "\t" << m[11] << "\t|" << std::endl;
	std::cout << "[\t" << m[12] << "\t" << m[13] << "\t" << m[14] << "\t" << m[15] << "\t]" << std::endl << std::endl;
}

void Matrix4::Transpose(void)
{
	*this = GetTranspose();
}

Matrix4 Matrix4::GetTranspose(void) const
{
	return Matrix4(m[0], m[4], m[8], m[12],
		m[1], m[5], m[9], m[13],
		m[2], m[6], m[10], m[14],
		m[3], m[7], m[11], m[15]);
}


#pragma region Define Operator

Matrix4 Matrix4::operator+(const Matrix4& mat) const		//overloaded operators
{
	return Matrix4(m[0] + mat.m[0],
		m[1] + mat.m[1],
		m[2] + mat.m[2],
		m[3] + mat.m[3],
		m[4] + mat.m[4],
		m[5] + mat.m[5],
		m[6] + mat.m[6],
		m[7] + mat.m[7],
		m[8] + mat.m[8],
		m[9] + mat.m[9],
		m[10] + mat.m[10],
		m[11] + mat.m[11],
		m[12] + mat.m[12],
		m[13] + mat.m[13],
		m[14] + mat.m[14],
		m[15] + mat.m[15]);
}

Matrix4 Matrix4::operator-(const Matrix4& mat) const		//overloaded operators
{
	return Matrix4(m[0] - mat.m[0],
		m[1] - mat.m[1],
		m[2] - mat.m[2],
		m[3] - mat.m[3],
		m[4] - mat.m[4],
		m[5] - mat.m[5],
		m[6] - mat.m[6],
		m[7] - mat.m[7],
		m[8] - mat.m[8],
		m[9] - mat.m[9],
		m[10] - mat.m[10],
		m[11] - mat.m[11],
		m[12] - mat.m[12],
		m[13] - mat.m[13],
		m[14] - mat.m[14],
		m[15] - mat.m[15]);
}

Matrix4 Matrix4::operator*(const Matrix4& mat) const
{
	//Optimize for matrices in which bottom row is (0, 0, 0, 1) in both matrices
	if (mat.m[12] == 0.0f && mat.m[13] == 0.0f && mat.m[14] == 0.0f && mat.m[15] == 1.0f &&
		m[12] == 0.0f && m[13] == 0.0f && m[14] == 0.0f && m[15] == 1.0f)
	{
		return Matrix4(
			mat.m[0] * m[0] + mat.m[4] * m[1] + mat.m[8] * m[2],
			mat.m[1] * m[0] + mat.m[5] * m[1] + mat.m[9] * m[2],
			mat.m[2] * m[0] + mat.m[6] * m[1] + mat.m[10] * m[2],
			mat.m[3] * m[0] + mat.m[7] * m[1] + mat.m[11] * m[2] + m[3],
			mat.m[0] * m[4] + mat.m[4] * m[5] + mat.m[8] * m[6],
			mat.m[1] * m[4] + mat.m[5] * m[5] + mat.m[9] * m[6],
			mat.m[2] * m[4] + mat.m[6] * m[5] + mat.m[10] * m[6],
			mat.m[3] * m[4] + mat.m[7] * m[5] + mat.m[11] * m[6] + m[7],
			mat.m[0] * m[8] + mat.m[4] * m[9] + mat.m[8] * m[10],
			mat.m[1] * m[8] + mat.m[5] * m[9] + mat.m[9] * m[10],
			mat.m[2] * m[8] + mat.m[6] * m[9] + mat.m[10] * m[10],
			mat.m[3] * m[8] + mat.m[7] * m[9] + mat.m[11] * m[10] + m[11],
			0,
			0,
			0,
			1
		);
	}

	//Optimise for when bottom row of 1st matrix is (0, 0, 0, 1)
	if (m[12] == 0.0f && m[13] == 0.0f && m[14] == 0.0f && m[15] == 1.0f)
	{
		return Matrix4(mat.m[0] * m[0] + mat.m[4] * m[1] + mat.m[8] * m[2] + mat.m[12] * m[3],
			mat.m[1] * m[0] + mat.m[5] * m[1] + mat.m[9] * m[2] + mat.m[13] * m[3],
			mat.m[2] * m[0] + mat.m[6] * m[1] + mat.m[10] * m[2] + mat.m[14] * m[3],
			mat.m[3] * m[0] + mat.m[7] * m[1] + mat.m[11] * m[2] + mat.m[15] * m[3],
			mat.m[0] * m[4] + mat.m[4] * m[5] + mat.m[8] * m[6] + mat.m[12] * m[7],
			mat.m[1] * m[4] + mat.m[5] * m[5] + mat.m[9] * m[6] + mat.m[13] * m[7],
			mat.m[2] * m[4] + mat.m[6] * m[5] + mat.m[10] * m[6] + mat.m[14] * m[7],
			mat.m[3] * m[4] + mat.m[7] * m[5] + mat.m[11] * m[6] + mat.m[15] * m[7],
			mat.m[0] * m[8] + mat.m[4] * m[9] + mat.m[8] * m[10] + mat.m[12] * m[11],
			mat.m[1] * m[8] + mat.m[5] * m[9] + mat.m[9] * m[10] + mat.m[13] * m[11],
			mat.m[2] * m[8] + mat.m[6] * m[9] + mat.m[10] * m[10] + mat.m[14] * m[11],
			mat.m[3] * m[8] + mat.m[7] * m[9] + mat.m[11] * m[10] + mat.m[15] * m[11],
			mat.m[12],
			mat.m[13],
			mat.m[14],
			mat.m[15]);
	}

	//Optimise for when bottom row of 2nd matrix is (0, 0, 0, 1)
	if (mat.m[12] == 0.0f && mat.m[13] == 0.0f &&
		mat.m[14] == 0.0f && mat.m[15] == 1.0f)
	{
		return Matrix4(mat.m[0] * m[0] + mat.m[4] * m[1] + mat.m[8] * m[2],
			mat.m[1] * m[0] + mat.m[5] * m[1] + mat.m[9] * m[2],
			mat.m[2] * m[0] + mat.m[6] * m[1] + mat.m[10] * m[2],
			mat.m[3] * m[0] + mat.m[7] * m[1] + mat.m[11] * m[2] + m[3],
			mat.m[0] * m[4] + mat.m[4] * m[5] + mat.m[8] * m[6],
			mat.m[1] * m[4] + mat.m[5] * m[5] + mat.m[9] * m[6],
			mat.m[2] * m[4] + mat.m[6] * m[5] + mat.m[10] * m[6],
			mat.m[3] * m[4] + mat.m[7] * m[5] + mat.m[11] * m[6] + m[7],
			mat.m[0] * m[8] + mat.m[4] * m[9] + mat.m[8] * m[10],
			mat.m[1] * m[8] + mat.m[5] * m[9] + mat.m[9] * m[10],
			mat.m[2] * m[8] + mat.m[6] * m[9] + mat.m[10] * m[10],
			mat.m[3] * m[8] + mat.m[7] * m[9] + mat.m[11] * m[10] + m[11],
			mat.m[0] * m[12] + mat.m[4] * m[13] + mat.m[8] * m[14],
			mat.m[1] * m[12] + mat.m[5] * m[13] + mat.m[9] * m[14],
			mat.m[2] * m[12] + mat.m[6] * m[13] + mat.m[10] * m[14],
			mat.m[3] * m[12] + mat.m[7] * m[13] + mat.m[11] * m[14] + m[15]);
	}

	return Matrix4(mat.m[0] * m[0] + mat.m[4] * m[1] + mat.m[8] * m[2] + mat.m[12] * m[3],
		mat.m[1] * m[0] + mat.m[5] * m[1] + mat.m[9] * m[2] + mat.m[13] * m[3],
		mat.m[2] * m[0] + mat.m[6] * m[1] + mat.m[10] * m[2] + mat.m[14] * m[3],
		mat.m[3] * m[0] + mat.m[7] * m[1] + mat.m[11] * m[2] + mat.m[15] * m[3],
		mat.m[0] * m[4] + mat.m[4] * m[5] + mat.m[8] * m[6] + mat.m[12] * m[7],
		mat.m[1] * m[4] + mat.m[5] * m[5] + mat.m[9] * m[6] + mat.m[13] * m[7],
		mat.m[2] * m[4] + mat.m[6] * m[5] + mat.m[10] * m[6] + mat.m[14] * m[7],
		mat.m[3] * m[4] + mat.m[7] * m[5] + mat.m[11] * m[6] + mat.m[15] * m[7],
		mat.m[0] * m[8] + mat.m[4] * m[9] + mat.m[8] * m[10] + mat.m[12] * m[11],
		mat.m[1] * m[8] + mat.m[5] * m[9] + mat.m[9] * m[10] + mat.m[13] * m[11],
		mat.m[2] * m[8] + mat.m[6] * m[9] + mat.m[10] * m[10] + mat.m[14] * m[11],
		mat.m[3] * m[8] + mat.m[7] * m[9] + mat.m[11] * m[10] + mat.m[15] * m[11],
		mat.m[0] * m[12] + mat.m[4] * m[13] + mat.m[8] * m[14] + mat.m[12] * m[15],
		mat.m[1] * m[12] + mat.m[5] * m[13] + mat.m[9] * m[14] + mat.m[13] * m[15],
		mat.m[2] * m[12] + mat.m[6] * m[13] + mat.m[10] * m[14] + mat.m[14] * m[15],
		mat.m[3] * m[12] + mat.m[7] * m[13] + mat.m[11] * m[14] + mat.m[15] * m[15]);
}

Matrix4 Matrix4::operator*(const float mat) const
{
	return Matrix4(m[0] * mat, m[1] * mat, m[2] * mat, m[3] * mat,
		m[4] * mat, m[5] * mat, m[6] * mat, m[7] * mat,
		m[8] * mat, m[9] * mat, m[10] * mat, m[11] * mat,
		m[12] * mat, m[13] * mat, m[14] * mat, m[15] * mat);
}

Matrix4 Matrix4::operator/(const float mat) const
{
	if (mat == 0.0f || mat == 1.0f) return  (*this);
	return Matrix4(*this) * 1.f / mat;
}

Matrix4 operator*(float scaleFactor, const Matrix4& mat)
{
	return mat * scaleFactor;
}

bool Matrix4::operator==(const Matrix4& mat) const
{
	for (int i = 0; i < 16; i++)
	{
		if (m[i] != mat.m[i])return false;
	}
	return true;
}

bool Matrix4::operator!=(const Matrix4& mat) const
{
	return !((*this) == mat);
}

void Matrix4::operator+=(const Matrix4& mat)
{
	(*this) = (*this) + mat;
}

void Matrix4::operator-=(const Matrix4& mat)
{
	(*this) = (*this) - mat;
}

void Matrix4::operator*=(const Matrix4& mat)
{
	(*this) = (*this) * mat;
}

void Matrix4::operator*=(const float mat)
{
	(*this) = (*this) * mat;
}

void Matrix4::operator/=(const float mat)
{
	(*this) = (*this) / mat;
}
Vector4 Matrix4::operator*(const Vector4 vector) const
{
	
		//Optimize for matrices in which bottom row is (0, 0, 0, 1)
		if (m[12] == 0.0f && m[13] == 0.0f && m[14] == 0.0f && m[15] == 1.0f)
		{
			return Vector4(m[0] * vector.GetX() + m[1] * vector.GetY() + m[2] * vector.GetZ() + m[3] * vector.GetW(),
				m[4] * vector.GetX() + m[5] * vector.GetY() + m[6] * vector.GetZ() + m[7] * vector.GetW(),
				m[8] * vector.GetX() + m[9] * vector.GetY() + m[10] * vector.GetZ() + m[11] * vector.GetW(),
				vector.GetW());
		}

		return Vector4(m[0] * vector.GetX() + m[1] * vector.GetY() + m[2] * vector.GetZ() + m[3] * vector.GetW(),
			m[4] * vector.GetX() + m[5] * vector.GetY() + m[6] * vector.GetZ() + m[7] * vector.GetW(),
			m[8] * vector.GetX() + m[9] * vector.GetY() + m[10] * vector.GetZ() + m[11] * vector.GetW(),
			m[12] * vector.GetX() + m[13] * vector.GetY() + m[14] * vector.GetZ() + m[15] * vector.GetW());
}
#pragma endregion

