#pragma once

#ifndef MODEL_H // include guard
#define MODEL_H

#include "Surface.h"
#include "Vector3.h"
#include <vector>
class Matrix4;


class Model
{

public:
	void AddVertices(Vector3& point);
	void AddSurfaces(Surface& surface);
	void PrintModelInfo();
	void PrintVertices();
	void PrintVertices(int number);
	void PrintSurfaces();
	void PrintSurfaces(int number);
	void SetNumVertices(int number);
	void SetNumSurfaces(int number);
	int GetNumVertices();
	int GetNumSurfaces();
	Vector3 GetPosition() const;
	void SetPosition(Vector3& position);
	std::vector<Vector3> GetVertices();
	std::vector<Surface> GetSurfaces();
	void LocalToWorld();
	inline void SetModelColor(Vector3& modelColor, float k_d) { this->modelColor = Vector3(modelColor); this->k_d = k_d; }
	inline Vector3 GetModelColor() { return this->modelColor; }
	inline float GetK_D() { return k_d; }
private:
	Vector3 worldOffset;
	std::vector<Vector3> vertices;
	std::vector<Surface> surfaces;
	int num_vertices;
	int num_surfaces;
	Vector3 modelColor;
	float k_d;
};

#endif

