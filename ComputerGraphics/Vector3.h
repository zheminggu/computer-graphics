#pragma once

#ifndef VECTOR3_H // include guard
#define VECTOR3_H

#include "Vector4.h"
	class Vector4;

	class Vector3
	{
	public:
		//constructors
		Vector3(void);
		Vector3(float x, float y, float z);
		Vector3(const float* vector);
		Vector3(const Vector3& vector);
		~Vector3(void) {}

		inline void Set(float x, float y, float z) {
			vec[0] = x;
			vec[1] = y;
			vec[2] = z;
		}
		void SetX(float number);
		void SetY(float number);
		void SetZ(float number);

		float GetX(void);
		float GetY(void);
		float GetZ(void);
		float* GetVec(void);

		//for safety
		float GetX(void) const;
		float GetY(void) const;
		float GetZ(void) const;
		void Print();

		void Zero(void);
		void One(void);
		float Length() const;
		void Normalize();
		Vector3 Cross(const Vector3& vector) const;
		
		static Vector3 Normalize(Vector3& vector);
		static Vector3 Cross(const Vector3& a, const Vector3& b);
		
		inline Vector4 ToVector4(void)
		{
			return Vector4(vec[0], vec[1], vec[2], 1.f);
		}

		Vector3 operator+(const Vector3& vector) const;
		Vector3 operator-(const Vector3& vector) const;
		float operator*(const Vector3& vector) const;
		Vector3 operator*(const float vector) const;
		Vector3 operator/(const float vector) const;

		//multiply by a float, eg 3*vec
		friend Vector3 operator*(float scaleFactor, const Vector3& vector);

		bool operator==(const Vector3& vector) const;
		bool operator!=(const Vector3& vector) const;

		//self-add etc
		void operator+=(const Vector3& vector);
		void operator-=(const Vector3& vector);
		void operator*=(const float vector);
		void operator/=(const float vector);

		//unary operators
		Vector3 operator-(void) const;
		Vector3 operator+(void) const;

		operator float* () const { return (float*)this; }
		operator const float* () const { return (const float*)this; }
	private:
		float vec[3];
	};

#endif