#include "Light.h"

Light::Light()
{
	this->localPosition = Vector3(0, 0, 0);
	this->worldPosition = Vector3(0, 0, 0);
	this->lightDirection = Vector3(0, 0, 0);
	this->lightColor = Vector3(0, 0, 0);
	this->k_s = 0.f;
	this->n = 0;
}

Light::Light(Vector3& direction, Vector3& color)
{
	this->localPosition = Vector3(0, 0, 0);
	this->worldPosition = Vector3(0, 0, 0);
	this->lightDirection = Vector3(direction);
	this->lightColor = Vector3(color);
	this->k_s = 0.f;
	this->n = 0;

}

Light::Light(Vector3& direction, Vector3& color, int n, float k_s)
{
	this->localPosition = Vector3(0, 0, 0);
	this->worldPosition = Vector3(0, 0, 0);
	this->lightDirection = Vector3(direction);
	this->lightColor = Vector3(color);
	this->n = n;
	this->k_s = k_s;
}

Light::Light(Vector3& worldPosition, Vector3& direction, Vector3& color)
{
	this->localPosition = Vector3(0, 0, 0);
	this->worldPosition = Vector3(worldPosition);
	this->lightDirection = Vector3(direction);
	this->lightColor = Vector3(color);
	this->k_s = 0.f;
	this->n = 0;
}

Light::~Light()
{
}


void Light::SetModelLightAttribute(float k_s, int n)
{
	this->k_s = k_s;
	this->n = n;
}

