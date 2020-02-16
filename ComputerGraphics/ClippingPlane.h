#pragma once
#ifndef CLIPPINGPLANE_H
#define CLIPPINGPLANE_H

class ClippingPlane
{
public:
	ClippingPlane();
	ClippingPlane(float distance);
	ClippingPlane(float distance, float height);
	~ClippingPlane();
	float GetDistance();
	float GetHeight();
	void SetHeight(float height);
private:
	float distance;
	float height;
};


#endif // !CLIPPINGPLANE_H
