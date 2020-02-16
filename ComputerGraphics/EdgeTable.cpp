#include "EdgeTable.h"
#include <iostream>
#include "Math.h"

EdgeTable::EdgeTable()
{
}

EdgeTable::~EdgeTable()
{
}

void EdgeTable::AddEdge(ModelEdge& model_edge)
{
	int height =(int) model_edge.height;
	if (height >SCREEN_HEIGHT)
	{
		height = SCREEN_HEIGHT;
	}
	if (height < 0)
	{
		height = 0;
	}
	if (this->edge_list.count(height)==0)
	{
		std::vector<ModelEdge> new_edge_list;
		new_edge_list.push_back(model_edge);
		edge_list[height] = new_edge_list;
	}
	else
	{
		edge_list[height].push_back(model_edge);
	}
}

void EdgeTable::Print()
{
	for (auto h_edge : this->edge_list )
	{
		std::cout << "height "<<h_edge.first <<": "<< std::endl;
		for (auto e : h_edge.second) {
			e.Print();
		}
		std::cout << std::endl;
	}
}
