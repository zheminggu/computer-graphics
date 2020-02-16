#include "ClippingPlane.h"

ClippingPlane::ClippingPlane(){
	distance = -1.f;
	height = -1.f;
}

ClippingPlane::ClippingPlane(float distance)
{
	this->distance = distance;
	this->height = -1.f;
}

ClippingPlane::ClippingPlane(float distance, float height)
{
	this->distance = distance;
	this->height = height;
}

ClippingPlane::~ClippingPlane()
{
}
float ClippingPlane::GetDistance()
{
	return distance;
}
float ClippingPlane::GetHeight()
{
	return height;
}

void ClippingPlane::SetHeight(float height)
{
	this->height = height;
}

