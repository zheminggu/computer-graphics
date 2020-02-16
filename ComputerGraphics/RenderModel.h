#pragma once
#ifndef RENDERMODEL_H
#define RENDERMODEL_H
#include "Surface.h"
#include "Vector4.h"
#include <vector>
class Vector3;
class Matrix4;
class EdgeTable;

class RenderModel
{
public:
	RenderModel();
	~RenderModel();
	void AddVertices(Vector4& point);
	void AddSurfaces(Surface& surface);
	void LeftProduct(Matrix4& mat);
	void DrawModel();
	void Print();
	void PrintVertices();
	void PrintVertices(int number);
	void PrintSurfaces();
	void PrintSurfaces(int number);
	void CalculateColor();
	void RegulateModel();
	std::vector<EdgeTable> CreateEdgeTable();

	Vector4 rgbToHsl(float r, float g, float b);

private:
	std::vector<Vector4> vertices;
	std::vector<Surface> surfaces;
	std::vector<Vector4> vertice_color;

};


#endif // !RENDERMODEL_H
