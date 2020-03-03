#pragma once

#ifndef VECTOR4_H // include guard
#define VECTOR4_H
	class Vector3;

	class Vector4 {
	public:
		//constructors
		Vector4(void);
		Vector4(float x, float y, float z, float w);
		Vector4(const float* vector);
		Vector4(const Vector4& vector);
		Vector4(const Vector3& vector);
		~Vector4(void) {}

		inline float GetX(void) { return vec[0]; }
		inline float GetY(void) { return vec[1]; }
		inline float GetZ(void) { return vec[2]; }
		inline float GetW(void) { return vec[3]; }

		inline void Add(float x, float y, float z, float w) {
			vec[0] += x;
			vec[1] += y;
			vec[2] += z;
			vec[3] += w;
		}

		inline void Set(float x, float y, float z, float w) {
			vec[0] = x;
			vec[1] = y;
			vec[2] = z;
			vec[3] = w;
		}
		void SetX(float number);
		void SetY(float number);
		void SetZ(float number);
		void SetW(float number);

		//for safety 
		inline float GetX(void) const { return this->vec[0]; }
		inline float GetY(void) const { return this->vec[1]; }
		inline float GetZ(void) const { return this->vec[2]; }
		inline float GetW(void) const { return this->vec[3]; }

		inline void ToPoint(void) {
			if (vec[3] != 0.0f && vec[3] != 1.0f)
			{
				vec[0] /= vec[3];
				vec[1] /= vec[3];
				vec[2] /= vec[3];
				vec[3] /= vec[3];
			}
			
		}
		void Print(void);

		void Zero(void);
		void One(void);
		float Dot(const Vector4& vector);

		Vector3 ToVector3(void);

		Vector4 operator+(const Vector4& vector) const;
		Vector4 operator-(const Vector4& vector) const;
		Vector4 operator*(const float vector) const;
		Vector4 operator/(const float vector) const;
		friend Vector4 operator*(float scaleFactor, const Vector4& vector);

		bool operator==(const Vector4& vector) const;
		bool operator!=(const Vector4& vector) const;

		//self-add etc
		void operator+=(const Vector4& vector);
		void operator-=(const Vector4& vector);
		void operator*=(const float vector);
		void operator/=(const float vector);

		//unary operators
		Vector4 operator-(void) const;
		Vector4 operator+(void) const;

		operator float* () const { return (float*)this; }
		operator const float* () const { return (const float*)this; }
	private:

		float vec[4];
	};


#endif