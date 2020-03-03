#pragma once
#ifndef MODELEDGE_H
#define MODELEDGE_H
#include "Vector3.h"
#include "Vector4.h"

class Vector3;
class Vector4;

class ModelEdge
{
public:
	ModelEdge(int height, float ymax, float xmin, float slope, Vector4& start_color, Vector4& color_slope,Vector3& start_vector, Vector3& vector_slope, float start_z, float z_slope);
	~ModelEdge();
	void Print();

public:
	int height;
	float Ymax;
	float Xmin;
	float slope;
	Vector4 start_color;
	Vector4 color_slope;
	Vector3 start_vector;
	Vector3 vector_slope;
	float start_z;
	float z_slope;
};


#endif // !MODELEDGE_H
