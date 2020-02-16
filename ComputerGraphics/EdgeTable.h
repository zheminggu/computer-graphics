#pragma once
#ifndef EDGETABLE_H
#define EDGETABLE_H
#include<map>
#include<vector>
#include "ModelEdge.h"
class ModelEdge;
class EdgeTable
{
public:
	EdgeTable();
	~EdgeTable();
	void AddEdge(ModelEdge& model_edge);
	void Print();
private:

public:
	// dictionary of the edge
	std::map<int, std::vector<ModelEdge>> edge_list;
};



#endif // !EDGETABLE_H
