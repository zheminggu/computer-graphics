#pragma once
#ifndef RENDERMODEL_H
#define RENDERMODEL_H
#include "Surface.h"
#include "Vector4.h"
#include "Light.h"
#include <vector>
class Vector3;
class Matrix4;
class EdgeTable;
class Light;

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
	void CalculateColor(Vector3& cameraDirection, std::vector<Light>& lights, Vector3& worldColor, float k_a);
	static Vector4 CalculateColor(Vector3& vector, Vector3& cameraDirection, std::vector<Light>& lights, Vector3& worldColor, Vector3& modelColor, float k_a, float k_d);
	void RegulateModel();
	std::vector<EdgeTable> CreateEdgeTable();
	void InitVerticeVector();
	inline void SetModelColor(Vector3& modelColor, float k_d) { this->modelColor = Vector3(modelColor); this->k_d = k_d; }
	inline Vector3 GetModelColor() { return this->modelColor; }
	inline float GetK_D() { return k_d; }
private:
	std::vector<Vector4> vertices;
	std::vector<Surface> surfaces;
	std::vector<Vector4> vertice_color;
	std::vector<Vector3> vertice_vector;
	Vector3 modelColor;
	float k_d;
};


#endif // !RENDERMODEL_H
