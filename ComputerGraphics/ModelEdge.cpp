#include "ModelEdge.h"
#include <iostream>
#include <iomanip>

ModelEdge::ModelEdge(int height, float ymax, float xmin, float slope, Vector4& start_color, Vector4& color_slope,Vector3& start_vector, Vector3& vector_slope, float start_z, float z_slope)
{
	this->height = height;
	this->Ymax = ymax;
	this->Xmin = xmin;
	this->slope = slope;
	this->start_color = Vector4(start_color);
	this->color_slope = Vector4(color_slope);
	this->start_vector = Vector3(start_vector);
	this->vector_slope = Vector3(vector_slope);
	this->start_z = start_z;
	this->z_slope = z_slope;
}

ModelEdge::~ModelEdge()
{
	
}

void ModelEdge::Print()
{
	std::cout << "[Y:" << (int)(this->Ymax) << ", X:";
	std::cout << std::fixed << std::setprecision(2) << this->Xmin;
	std::cout << ", s: ";
	std::cout << std::fixed << std::setprecision(2) << this->slope;
	std::cout << ", z : ";
	std::cout << std::fixed << std::setprecision(2) << this->start_z;
	std::cout << ", zs : ";
	std::cout << std::fixed << std::setprecision(6) << this->z_slope;
	std::cout << "]";
}
