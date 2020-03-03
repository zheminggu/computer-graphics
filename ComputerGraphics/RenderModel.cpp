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


void RenderModel::CalculateColor(Vector3& cameraDirection, std::vector<Light>& lights, Vector3& worldColor, float k_a)
{

	int n = 0;
	float k_s = 0.f;
	float smoothstaff = 0.f;
	Vector3 H = Vector3();
	Vector3 lightColor = Vector3();
	Vector3 color;
	Vector3 lightDir = Vector3();
	for (auto& light: lights)
	{
		n = light.GetN();
		k_s = light.GetK_S();
		lightDir = light.GetLightDirection();
		smoothstaff = 0;
		H = lightDir.Normalize() + -cameraDirection.Normalize();
		H = H.Normalize();
		lightColor = light.GetLightColor();
		this->vertice_color.clear();
		for (int i = 0; i < this->vertices.size(); i++)
		{
			if (vertice_vector[i] * H > 0)
			{
				smoothstaff = powf(vertice_vector[i] * H, n);
			}
			else
			{
				smoothstaff = 0;
			}
			color = k_a * worldColor + this->modelColor *this->k_d * (vertice_vector[i] * lightDir) + lightColor * smoothstaff * k_s;

			vertice_color.push_back(Vector4(color.GetX(), color.GetY(), color.GetZ(), 255));
			//vertice_color.push_back(Vector4(vertice_vector[i].GetX()*255, vertice_vector[i].GetY() * 255, vertice_vector[i].GetZ() * 255, 255));
		}
	}
}

Vector4 RenderModel::CalculateColor(Vector3& vector, Vector3& cameraDirection, std::vector<Light>& lights, Vector3& worldColor,Vector3& modelColor, float k_a, float k_d)
{

	int n = 0;
	float k_s = 0.f;
	float smoothstaff = 0.f;
	Vector3 H = Vector3();
	Vector3 lightColor = Vector3();
	Vector3 color = k_a * worldColor;
	Vector3 lightDir = Vector3();
	vector = vector.Normalize();
	for (auto& light : lights)
	{
		n = light.GetN();
		k_s = light.GetK_S();
		lightDir = light.GetLightDirection();
		smoothstaff = 0;
		H = lightDir.Normalize() + -cameraDirection.Normalize();
		H = H.Normalize();
		lightColor = light.GetLightColor();
		if (vector * H > 0)
		{
			smoothstaff = powf(vector * H, n);
		}
		color += modelColor * k_d* (vector* lightDir) + lightColor * smoothstaff * k_s;
		//color = 255* vector/* + Vector3(255, 255, 255) * smoothstaff * k_s*/;
	}
	return Vector4(color.GetX(), color.GetY(), color.GetZ(), 255);
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
	Vector3 current_vector;
	Vector3 next_vector;
	float current_z = 0;
	float next_z = 0;
	float Ymax = 0;
	float Xmin = 0;
	float height = 0;
	float slope = 0;
	Vector4 start_color;
	Vector4 color_slope;
	Vector3 start_vector;
	Vector3 vector_slope;
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
				current_vector = vertice_vector[current_surface[i]];
				next_vector = vertice_vector[current_surface[i + 1]];
			}
			else {
				current_point = vertices[current_surface[i]];
				next_point = vertices[current_surface[0]];
				current_color = vertice_color[current_surface[i]];
				next_color = vertice_color[current_surface[0]];
				current_vector = vertice_vector[current_surface[i]];
				next_vector = vertice_vector[current_surface[0]];
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
				start_vector = next_vector;
			}
			else //the current is on the bottom
			{
				Ymax = ny;
				Xmin = cx;
				height = cy;
				start_color = current_color;
				start_z = current_z;
				start_vector = current_vector;
			}

			if ((int)cy ==(int)ny)
			{
				continue;
				/*slope = 0;
				color_slope = Vector4(0, 0, 0, 0);
				z_slope = 0;*/
			}
			else {
				slope = (cx - nx) / (cy - ny);
				color_slope = (current_color - next_color) / (cy - ny);
				z_slope = (current_z - next_z) / (cy - ny);
				vector_slope = (current_vector -next_vector)/ (cy - ny);
			}
			
			ModelEdge edge = ModelEdge(height, Ymax, Xmin, slope, start_color, color_slope,start_vector, vector_slope, start_z, z_slope);
			edges_of_surface.push_back(edge);
		}

		//sort edges of surface
		std::sort(edges_of_surface.begin(), edges_of_surface.end(), compareEdges_YXS);

		newEdgeTable = EdgeTable();
		newEdgeTable.SetModelColor(modelColor, k_d);
		for (auto& edge : edges_of_surface) {
			newEdgeTable.AddEdge(edge);
		}
		edge_tables_this_model.push_back(newEdgeTable);
	}

	return edge_tables_this_model;
}

void RenderModel::InitVerticeVector()
{
	vertice_vector.clear();
	for (int  i = 0; i < vertices.size(); i++)
	{
		vertice_vector.push_back(Vector3(0, 0, 0));
	}
	Vector3 V1;
	Vector3 V2;
	Vector3 Np;
	std::vector<int> sur;
	for (auto s :surfaces)
	{
		sur = s.GetSurface();
		// first one
		V1 = (vertices[sur[0]] - vertices[sur[sur.size()-1]]).ToVector3();
		V2 = (vertices[sur[1]] - vertices[sur[0]]).ToVector3();
		Np = Vector3::Cross(V2, V1);
		vertice_vector[sur[0]].Add(Np.GetX(), Np.GetY(), Np.GetZ());
		//last one
		V1 = (vertices[sur[sur.size() - 1]] - vertices[sur[sur.size() - 2]]).ToVector3();
		V2 = (vertices[sur[0]] - vertices[sur[sur.size() - 1]]).ToVector3();
		Np = Vector3::Cross(V2, V1);
		vertice_vector[sur[sur.size() - 1]].Add(Np.GetX(), Np.GetY(), Np.GetZ());

		for (int i = 1; i < sur.size()-1; i++)
		{
			V1 = (vertices[sur[i]] - vertices[sur[i-1]]).ToVector3();
			V2 = (vertices[sur[i+1]] - vertices[sur[i]]).ToVector3();
			Np = Vector3::Cross(V2, V1);
			vertice_vector[sur[i]].Add(Np.GetX(), Np.GetY(), Np.GetZ());
		}
		
	}

	for (int i = 0; i < vertices.size(); i++)
	{
		vertice_vector[i].Normalize();
		//vertice_vector[i] =-1* vertice_vector[i];
		//vertice_vector[i].Print();
	}

}

