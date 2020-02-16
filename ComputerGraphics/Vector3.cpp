//#include "Math.h"
//using namespace Vector;

#include <memory.h>
#include <iostream>
#include <string>
#include "Vector3.h"
#include "Vector4.h"

Vector3::Vector3()
{
	memset(vec , 0, sizeof(float) * 3);
}

Vector3::Vector3(float x, float y, float z)
{
	vec[0] = x; vec[1] = y; vec[2] = z;
}

Vector3::Vector3(const float* vector)
{
	memcpy(vec, vector, sizeof(float) * 3);
}

Vector3::Vector3(const Vector3& vector)
{
	memcpy(vec, vector.vec, sizeof(float) * 3);
}

void Vector3::SetX(float number)
{
	this->vec[0] = number;
}

void Vector3::SetY(float number)
{
	this->vec[1] = number;
}

void Vector3::SetZ(float number)
{
	this->vec[2] = number;
}

inline float Vector3::GetX()
{
	return this->vec[0];
}

inline float Vector3::GetY()
{
	return this->vec[1];
}

inline float Vector3::GetZ()
{
	return this->vec[2];
}

float* Vector3::GetVec()
{
	return vec;
}

inline float Vector3::GetX() const
{
	return this->vec[0];
}

inline float Vector3::GetY() const {
	return this->vec[1];
}

inline float Vector3::GetZ() const
{
	return this->vec[2];
}

void Vector3::Print()
{
	std::cout << std::to_string(GetX()) + " " + std::to_string(GetY()) + " " + std::to_string(GetZ()) << std::endl;
}

void Vector3::Zero(void)
{
	memset(vec, 0, 3 * sizeof(float));
}

void Vector3::One(void)
{
	vec[0] = vec[1] = vec[2] = 1.f;	
}

float Vector3::Length() const
{
	return (float)sqrt((vec[0] * vec[0]) + (vec[1] * vec[1]) + (vec[2] * vec[2]));
}

void Vector3::Normalize()
{
	float length = Length();
	if (length == 1 || length == 0)return;
	float scalefactor = 1.0f / length;
	vec[0] *= scalefactor;
	vec[1] *= scalefactor;
	vec[2] *= scalefactor;
}

Vector3 Vector3::Cross(const Vector3& vector) const
{
	return Vector3(vec[1] * vector.vec[2] - vec[2] * vector.vec[1], vec[2] * vector.vec[0] - vec[0] * vector.vec[2], vec[0] * vector.vec[1] - vec[1] * vector.vec[0]);
}



Vector3 Vector3::Normalize(Vector3& vector)
{
	float length = vector.Length();
	if (length == 1 || length == 0)	return Vector3(vector.GetX(), vector.GetY(), vector.GetZ());
	float scalefactor = 1.0f / length;
	return Vector3(vector.GetX() * scalefactor, vector.GetY() * scalefactor, vector.GetZ() * scalefactor);
}

Vector3 Vector3::Cross(const Vector3& a, const Vector3& b)
{
	return Vector3(a.vec[1] * b.vec[2] - a.vec[2] * b.vec[1], a.vec[2] * b.vec[0] - a.vec[0] * b.vec[2], a.vec[0] * b.vec[1] - a.vec[1] * b.vec[0]);
}

// Vector4 Vector3::ToVector4(void) 
//{
//	return Vector4(vec[0], vec[1], vec[2], 1.f);
//}



#pragma region Define Operator

Vector3 Vector3::operator+(const Vector3& vector) const
{
	return Vector3(vec[0] + vector.vec[0], vec[1] + vector.vec[1], vec[2] + vector.vec[2]);
}

Vector3 Vector3::operator-(const Vector3& vector) const
{
	return Vector3(vec[0] - vector.vec[0], vec[1] - vector.vec[1], vec[2] - vector.vec[2]);
}

float Vector3::operator*(const Vector3& vector) const
{
	return vec[0]*vector.GetX()+vec[1]*vector.GetY() + vec[2] * vector.GetZ();
}

Vector3 Vector3::operator*(const float vector) const
{
	return Vector3(vec[0] * vector, vec[1] * vector, vec[2] * vector);
}

Vector3 Vector3::operator/(const float vector) const
{
	return (vector == 0.0f) ? Vector3(0.0f, 0.0f, 0.0f) : Vector3(vec[0] / vector, vec[1] / vector, vec[2] / vector);
}

//multiply by a float, eg 3*vec
Vector3 operator*(float scaleFactor, const Vector3& vector) {
	return vector * scaleFactor;
}

bool Vector3::operator==(const Vector3& vector) const {
	if (vec[0] == vector.vec[0] && vec[1] == vector.vec[1] && vec[2] == vector.vec[2]) return true;
	else return false;
}

bool Vector3::operator!=(const Vector3& vector) const
{
	return !((*this) == vector);
}

//self-add etc
void Vector3::operator+=(const Vector3& vector)
{
	vec[0] += vector.vec[0];
	vec[1] += vector.vec[1];
	vec[2] += vector.vec[2];
}

void Vector3::operator-=(const Vector3& vector)
{
	vec[0] -= vector.vec[0];
	vec[1] -= vector.vec[1];
	vec[2] -= vector.vec[2];
}

void Vector3::operator*=(const float vector)
{
	vec[0] *= vector;
	vec[1] *= vector;
	vec[2] *= vector;
}

void Vector3::operator/=(const float vector)
{
	if (vector == 0.0f) return;
	else
	{
		vec[0] /= vector;
		vec[1] /= vector;
		vec[2] /= vector;
	}
}


//unary operators
Vector3 Vector3::operator-(void) const
{
	return Vector3(-vec[0], -vec[1], -vec[2]);
}

Vector3 Vector3::operator+(void) const
{
	return *this;
}

#pragma endregion






