//#include "Math.h"
//using namespace Vector;

#include "Vector4.h"
#include "Vector3.h"
#include <memory.h>
#include <iostream>

Vector4::Vector4() {
	Zero();
}

Vector4::Vector4(float x, float y, float z, float w)
{
	this->vec[0] = x; 
	this->vec[1] = y; 
	this->vec[2] = z; 
	this->vec[3] = w;
}

Vector4::Vector4(const float* newv)
{
	memcpy(vec, newv, 4 * sizeof(float));
}

Vector4::Vector4(const Vector4& newv)
{
	memcpy(vec, newv.vec, 4 * sizeof(float));
}

Vector4::Vector4(const Vector3 & vector)
{
	vec[0] = vector.GetX(); vec[1] = vector.GetY(); vec[2] = vector.GetZ(); vec[3] = 1.f;
}

//float Vector4::GetX(void)
//{
//	return this->vec[0];
//}
//
//float Vector4::GetY(void)
//{
//	return this->vec[1];
//}
//
//float Vector4::GetZ(void)
//{
//	return this->vec[2];
//}
//
//float Vector4::GetW(void)
//{
//	return this->vec[3];
//}

void Vector4::SetX(float number)
{
	vec[0] = number;
}

void Vector4::SetY(float number)
{
	vec[1] = number;
}

void Vector4::SetZ(float number)
{
	vec[2] = number;
}

void Vector4::SetW(float number)
{
	vec[3] = number;
}

//inline float Vector4::GetX(void) const
//{
//	return this->vec[0];
//}

//float Vector4::GetY(void) const
//{
//	return this->vec[1];
//}
//
//float Vector4::GetZ(void) const
//{
//	return this->vec[2];
//}
//
//float Vector4::GetW(void) const
//{
//	return this->vec[3];
//}

void Vector4::Print(void)
{
	std::cout << GetX()<< " " <<GetY() << " " << GetZ() << " " << GetW() << std::endl;
}


void Vector4::Zero(void) {
	this->vec[0] = 0; 
	this->vec[1] = 0; 
	this->vec[2] = 0; 
	this->vec[3] = 0;
}

void Vector4::One(void) {
	this->vec[0] = 1;
	this->vec[1] = 1;
	this->vec[2] = 1;
	this->vec[3] = 1;
}

float Vector4::Dot(const Vector4& vector)
{
	return vec[0] * vector.vec[0] + vec[1] * vector.vec[1] + vec[2] * vector.vec[2] + vec[3] * vector.vec[3];
}


Vector3 Vector4::ToVector3(void) 
{
	if (vec[3] == 0.0f || vec[3] == 1.0f) 
	{
		return Vector3(vec[0], vec[1], vec[2]);
	}
	else
	{
		return Vector3(vec[0] / vec[3], vec[1] / vec[3], vec[2] / vec[3]);
	}
}

#pragma region Define operator

Vector4 Vector4::operator+(const Vector4& vector) const
{
	return Vector4(vec[0] + vector.vec[0], vec[1] + vector.vec[1], vec[2] + vector.vec[2], vec[3] + vector.vec[3]);
}

Vector4 Vector4::operator-(const Vector4& vector) const
{
	return Vector4(vec[0] - vector.vec[0], vec[1] - vector.vec[1], vec[2] - vector.vec[2], vec[3] - vector.vec[3]);
}

Vector4 Vector4::operator*(const float vector) const
{
	return Vector4(vec[0] * vector, vec[1] * vector, vec[2] * vector, vec[3] * vector);
}

Vector4 Vector4::operator/(const float vector) const
{
	return vector == 0.0f ? Vector4(0.0f, 0.0f, 0.0f, 0.0f) : Vector4(vec[0] / vector, vec[1] / vector, vec[2] / vector, vec[3] / vector);
}

//multiply by a float, eg 3*vec
Vector4 operator*(float scaleFactor, const Vector4& vector) {
	return vector * scaleFactor;
}

bool Vector4::operator==(const Vector4& vector) const {
	if (vec[0] == vector.vec[0] && vec[1] == vector.vec[1] && vec[2] == vector.vec[2] && vec[3] == vector.vec[3]) return true;
	else return false;
}

bool Vector4::operator!=(const Vector4& vector) const
{
	return !((*this) == vector);
}

//self-add etc
void Vector4::operator+=(const Vector4& vector)
{
	vec[0] += vector.vec[0]; vec[1] += vector.vec[1]; vec[2] += vector.vec[2]; vec[3] += vector.vec[3];
}

void Vector4::operator-=(const Vector4& vector)
{
	vec[0] -= vector.vec[0]; vec[1] -= vector.vec[1]; vec[2] -= vector.vec[2]; vec[3] -= vector.vec[3];
}

void Vector4::operator*=(const float vector)
{
	vec[0] *= vector;
	vec[1] *= vector;
	vec[2] *= vector;
	vec[3] *= vector;
}

void Vector4::operator/=(const float vector)
{
	if (vector == 0.0f)	return;
	else
	{
		vec[0] /= vector;
		vec[1] /= vector;
		vec[2] /= vector;
		vec[3] /= vector;
	}
}

//unary operators
Vector4 Vector4::operator-(void) const
{
	return Vector4(-vec[0], -vec[1], -vec[2], -vec[3]);
}

Vector4 Vector4::operator+(void) const
{
	return (*this);
}
#pragma endregion

