#pragma once
#ifndef LIGHT_H
#define LIGHT_H

#include "Vector3.h"


class Light
{
public:
	Light();
	Light(Vector3& direction, Vector3& color);
	Light(Vector3& direction, Vector3& color, int n, float k_s);
	Light(Vector3& worldPosition, Vector3& direction, Vector3& color);
	~Light();

	inline Vector3 GetLocalPosition() { return this->localPosition; }
	inline Vector3 GetWorldPosition() { return this->worldPosition; }
	inline Vector3 GetLightDirection() { return this->lightDirection; }
	inline Vector3 GetLightColor() { return this->lightColor; }
	inline int GetN() { return this->n; }
	inline float GetK_S() { return this->k_s; }

	inline void SetWorldPosition(Vector3& position) { this->worldPosition = Vector3(position); }
	inline void SetLightDirection(Vector3& direction) { this->lightDirection = Vector3(direction); }
	inline void SetLightColor(Vector3& color) { this->lightColor = Vector3(color); }
	inline void SetN(int n) { this->n = n; }
	inline void SetK_S(float k_s) { this->k_s = k_s; }
	void SetModelLightAttribute(float k_s, int n);


private:
	Vector3 localPosition;
	Vector3 worldPosition;
	Vector3 lightDirection;
	Vector3 lightColor;
	float k_s;
	int n;

};


#endif // !LIGHTS_H
