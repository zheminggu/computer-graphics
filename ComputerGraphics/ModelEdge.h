#pragma once
#ifndef MODELEDGE_H
#define MODELEDGE_H

class Vector4;
class ModelEdge
{
public:
	ModelEdge(int height, float ymax, float xmin, float slope, Vector4& start_color, Vector4& color_slope, float start_z, float z_slope);
	~ModelEdge();
	void Print();

public:
	int height;
	float Ymax;
	float Xmin;
	float slope;
	Vector4* start_color;
	Vector4* color_slope;
	float start_z;
	float z_slope;
};


#endif // !MODELEDGE_H
