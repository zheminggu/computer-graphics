#pragma once
#ifndef EDGETABLE_H
#define EDGETABLE_H
#include<map>
#include<vector>
#include "ModelEdge.h"
#include "Vector3.h"

class Vector3;
class ModelEdge;
class EdgeTable
{
public:
	EdgeTable();
	~EdgeTable();
	void AddEdge(ModelEdge& model_edge);
	void Print();
	inline void SetModelColor(Vector3& color, float k_d) { this->modelColor = color; this->k_d = k_d; }
	inline Vector3 GetModelColor() { return modelColor; }
	inline float GetK_D() { return k_d; }
private:

public:
	// dictionary of the edge
	std::map<int, std::vector<ModelEdge>> edge_list;
	Vector3 modelColor;
	float k_d;
};



#endif // !EDGETABLE_H
