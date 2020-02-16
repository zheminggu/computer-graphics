#include <iostream>
#include <algorithm>
#include "RenderModel.h"
#include "Matrix4.h"
#include "Vector3.h"
#include "Draw.h"
#include "EdgeTable.h"
#include "ModelEdge.h"
#include "Math.h"
#include "Debug.h"
#include "World.h"

RenderModel::RenderModel()
{
	
}

RenderModel::~RenderModel()
{
}

void RenderModel::AddVertices(Vector4& point)
{
	vertices.push_back(point);
}

void RenderModel::AddSurfaces(Surface& surface)
{
	surfaces.push_back(surface);
}

void RenderModel::LeftProduct(Matrix4& mat)
{
	for (auto & v : vertices) {
		v = mat * v;
	}
}

void RenderModel::DrawModel() {
	Vector3 startPoint; 
	Vector3 endPoint;
	std::vector<int> temp_s;

	int surface_size = -1;
	for (auto & s : surfaces) {
		temp_s = s.GetSurface();
		surface_size= temp_s.size();

		for (int i = 0; i < surface_size;i++) {
			if (i== surface_size-1)
			{
				startPoint = vertices[temp_s[i]].ToVector3();
				endPoint = vertices[temp_s[0]].ToVector3();
				
			}
			else {
				startPoint = vertices[temp_s[i]].ToVector3();
				endPoint = vertices[temp_s[i+1]].ToVector3();
			}
			Draw::DrawLine(startPoint, endPoint);

		}
		////testing
		//break;
	}
}

void RenderModel::Print()
{
	std::cout << "Printing Render Model " <<std::endl;
	PrintVertices(10);
	std::cout << "............" << std::endl << std::endl;
	PrintSurfaces(10);
	std::cout << "............" << std::endl << std::endl;

}

void RenderModel::PrintVertices()
{
	std::cout << "actual number of vertices: " << this->vertices.size() << std::endl;
	for (auto i = 0; i < this->vertices.size(); i++)
	{
		this->vertices[i].Print();
	}
}

void RenderModel::PrintVertices(int number)
{
	std::cout << "actual number of vertices: " << this->vertices.size() << std::endl;
	if (number < this->vertices.size())
	{
		for (auto i = 0; i < number; i++)
		{
			this->vertices[i].Print();
		}
	}
	else
	{
		for (auto i = 0; i < this->vertices.size(); i++)
		{
			this->vertices[i].Print();
		}
	}

}

void RenderModel::PrintSurfaces()
{
	std::cout << "actual number of surfaces: " << this->surfaces.size() << std::endl;
	for (auto i = 0; i < this->surfaces.size(); i++)
	{
		this->surfaces[i].Print();
	}
}

void RenderModel::PrintSurfaces(int number)
{
	std::cout << "actual number of surfaces: " << this->surfaces.size() << std::endl;
	if (number < this->surfaces.size())
	{
		for (auto i = 0; i < number; i++)
		{
			this->surfaces[i].Print();
		}
	}
	else
	{
		for (auto i = 0; i < this->surfaces.size(); i++)
		{
			this->surfaces[i].Print();
		}
	}
}

std::vector<Vector4> global_vertice_color;
bool have_calculate_once = false;
void RenderModel::CalculateColor()
{
	if (have_calculate_once)
	{
		this->vertice_color = global_vertice_color;
	}
	else
	{
		this->vertice_color.clear();
		for (int i = 0; i < this->vertices.size(); i++)
		{
			//HslColor = Draw::rgbToHsl(rand() % 255 , rand() % 255, rand() % 255);
			this->vertice_color.push_back(Vector4(rand() % 255 / 255.f, rand() % 255 / 255.f, rand() % 255 / 255.f, 255));
			//this->vertice_color.push_back(Vector4(rand() % 255/255.f, 0, 0,255));
			//this->vertice_color.push_back(rgbToHsl(rand() % 255, rand() % 255, rand() % 255));
		}
		global_vertice_color = this->vertice_color;
		have_calculate_once = true;
	}
	
}

void RenderModel::RegulateModel()
{
	for (auto&v : this->vertices)
	{
		v.ToPoint();
	}
}

bool compareEdges_YXS(const ModelEdge& edge1, const ModelEdge& edge2) {
	if ((int)edge1.Ymax <(int) edge2.Ymax) return true;
	if ((int)edge1.Ymax == (int)edge2.Ymax) {
		if ((int)edge1.Xmin < (int)edge2.Xmin) return true;
		if ((int)edge1.Xmin == (int)edge2.Xmin)
		{
			return edge1.slope < edge2.slope;
		}
	}
	return false;
}



std::vector<EdgeTable> RenderModel::CreateEdgeTable()
{
	std::vector<EdgeTable> edge_tables_this_model;
	EdgeTable newEdgeTable = EdgeTable();
	Vector4 current_point;
	Vector4 next_point;
	Vector4 current_color;
	Vector4 next_color;
	float current_z = 0;
	float next_z = 0;
	float Ymax = 0;
	float Xmin = 0;
	float height = 0;
	float slope = 0;
	Vector4 start_color;
	Vector4 color_slope;
	float start_z = 0;
	float z_slope = 0;
	float cx = 0;
	float cy = 0;
	float nx = 0;
	float ny = 0;
	std::vector<int> current_surface;
	std::vector<ModelEdge> edges_of_surface;

	for (auto& surface : this->surfaces) {
		edges_of_surface.clear();
		current_surface = surface.GetSurface();
		int size = current_surface.size();
		for (int i = 0; i < size; i++)
		{
			//init current point, next point, current color, next color, and current z, next z
			if (i < size - 1)
			{
				current_point = vertices[current_surface[i]];
				next_point = vertices[current_surface[i + 1]];
				current_color =vertice_color[current_surface[i]];
				next_color = vertice_color[current_surface[i + 1]];
			}
			else {
				current_point = vertices[current_surface[i]];
				next_point = vertices[current_surface[0]];
				current_color = vertice_color[current_surface[i]];
				next_color = vertice_color[current_surface[0]];
			}
			current_z = current_point.GetZ();
			next_z = next_point.GetZ();
			
			//---compare Y value to get Y max----

			cx = current_point.GetX();
			cy = current_point.GetY();
			nx = next_point.GetX();
			ny = next_point.GetY();
			cx = round(cx * (Screen_Weight / 2) + Screen_Weight/2);
			cy = round(cy * (Screen_Height / 2) + Screen_Height/2);
			nx = round(nx * (Screen_Weight / 2) + Screen_Weight/2);
			ny = round(ny * (Screen_Height / 2) + Screen_Height/2);
			//Debug::Log("cx",cx,"cy",cy);

			if (cy> ny) //if next point is on the bottom
			{
				Ymax = cy;
				Xmin = nx;
				height = ny;
				start_color = next_color;
				start_z = next_z;
			}
			else //the current is on the bottom
			{
				Ymax = ny;
				Xmin = cx;
				height = cy;
				start_color = current_color;
				start_z = current_z;
			}

			if ((int)cy ==(int)ny)
			{
				slope = 0;
				color_slope = Vector4(0, 0, 0, 0);
				z_slope = 0;
			}
			else {
				slope = (cx - nx) / (cy - ny);
				color_slope = (current_color - next_color) / (cy - ny);
				z_slope = (current_z - next_z) / (cy - ny);
			}

			
			ModelEdge edge = ModelEdge(height, Ymax, Xmin, slope, start_color, color_slope, start_z, z_slope);
			edges_of_surface.push_back(edge);
		}

		//sort edges of surface
		std::sort(edges_of_surface.begin(), edges_of_surface.end(), compareEdges_YXS);

		newEdgeTable = EdgeTable();
		for (auto& edge : edges_of_surface) {
			newEdgeTable.AddEdge(edge);
		}
		edge_tables_this_model.push_back(newEdgeTable);
	}

	return edge_tables_this_model;
}

/**
 * Converts an RGB color value to HSL. Conversion formula
 * adapted from http://en.wikipedia.org/wiki/HSL_color_space.
 * Assumes r, g, and b are contained in the set [0, 255] and
 * returns h, s, and l in the set [0, 1].
 *
 * @param   {number}  r       The red color value
 * @param   {number}  g       The green color value
 * @param   {number}  b       The blue color value
 * @return  {Array}           The HSL representation
 */

int maxmum(int a, int b, int c)
{
	int n = (a < b) ? b : a;
	return ((n < c) ? c : n);
}

int minimum(int a, int b, int c)
{
	int n = (a > b) ? b : a;
	return ((n > c) ? c : n);
}

float maxmum(float a, float b, float c)
{
	float n = (a < b) ? b : a;
	return ((n < c) ? c : n);
}

float minimum(float a, float b, float c)
{
	float n = (a > b) ? b : a;
	return ((n > c) ? c : n);
}


Vector4 RenderModel::rgbToHsl(float r, float g, float b) {
	int o_r = r;
	int o_g = g;
	int o_b = b;
	int max_c = maxmum((int)r, (int)g, (int)b);
	int min_c = minimum((int)r, (int)g, (int)b);
	r /= 255., g /= 255., b /= 255.;
	float max = maxmum(r, g, b);
	float min = minimum(r, g, b);
	float h, s, l = (max + min) / 2;



	if (max_c == min_c) {
		h = s = 0; // achromatic
	}
	else {
		float d = max - min;
		s = l > 0.5 ? d / (2 - max - min) : d / (max + min);
		if (max_c == o_r)
		{
			h = (g - b) / d + (g < b ? 6 : 0);
		}
		else if (max_c == o_g)
		{
			h = (b - r) / d + 2;
		}
		else
		{
			h = (r - g) / d + 4;
		}

		h /= 6;
	}

	return Vector4(h, s, l, 255);
}

