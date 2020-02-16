#pragma once
#ifndef MATRIX4_H // include guard
#define MATRIX4_H

	class Vector3;
	class Vector4;
	class Matrix4 {
	public:
		//constructors
		Matrix4() { Identity(); }
		Matrix4(float  m0, float  m1, float  m2, float  m3,
			float  m4, float  m5, float  m6, float  m7,
			float  m8, float  m9, float m10, float m11,
			float m12, float m13, float m14, float m15);
		Matrix4(const float* old);
		Matrix4(const Matrix4& old);
		//destructor
		~Matrix4() {}

		Vector4 GetRow(int rowIndex) const;
		Vector4 GetColumn(int cloumnIndex) const;

		void Identity();
		void Zero();
		void Print();

		void Transpose(void);
		Matrix4 GetTranspose(void) const;

		Matrix4 operator+(const Matrix4& mat) const;
		Matrix4 operator-(const Matrix4& mat) const;
		Matrix4 operator*(const Matrix4& mat) const;
		Matrix4 operator*(const float mat) const;
		Matrix4 operator/(const float mat) const;
		friend Matrix4 operator*(float scaleFactor, const Matrix4& mat);

		bool operator==(const Matrix4& mat) const;
		bool operator!=(const Matrix4& mat) const;

		//self-add etc
		void operator+=(const Matrix4& mat);
		void operator-=(const Matrix4& mat);
		void operator*=(const Matrix4& mat);
		void operator*=(const float mat);
		void operator/=(const float mat);

		Vector4 operator*(const Vector4 vector) const;


		operator float* () const { return (float*)this; }
		operator const float* () const { return (const float*)this; }
	private:
		float m[16];

	};

#endif