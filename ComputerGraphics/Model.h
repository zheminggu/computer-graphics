#pragma once

#ifndef MODEL_H // include guard
#define MODEL_H

#include "Surface.h"
#include "Vector3.h"
#include "Texture.h"
#include <vector>
class Matrix4;
class Texture;

class Model
{

public:
	Model() {
		rotate = false;
		degree = 0;
	}
	void AddVertices(Vector3& point);
	void AddSurfaces(Surface& surface);
	void AddTexture(Texture* texture); 
	void AddNormalTexture(Texture* texture);
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
	inline Texture* GetTexture() { return  this->texture; }
	inline Texture* GetNormalTexture() { return  this->normalTexture; }
	inline void SetTexture(Texture *texture) { this->texture = texture; }
	void OnUpdate();
private:
	Vector3 worldOffset;
	std::vector<Vector3> vertices;
	std::vector<Surface> surfaces;
	int num_vertices;
	int num_surfaces;
	Vector3 modelColor;
	float k_d;
	Texture* texture;
	Texture* normalTexture;
public:
	bool rotate;
	float degree;
	
};

#endif

