#include <iostream>
#include "Matrix4.h"
#include "Model.h"
#include "Vector4.h"
//#include "Vector3.h"
//#include "Surface.h"

void Model::AddVertices(Vector3& point)
{
	this->vertices.push_back(point);
}

void Model::AddSurfaces(Surface& surface)
{
	this->surfaces.push_back(surface);
}

void Model::AddTexture(Texture* texture)
{
	this->texture = texture;
}

void Model::AddNormalTexture(Texture* texture)
{
	this->normalTexture = texture;
}

void Model::PrintModelInfo()
{
	std::cout << "number of vertices: " <<this->num_vertices << std::endl;
	std::cout << "number of surfaces: " <<this->num_surfaces << std::endl;
	PrintVertices(10);
	std::cout << "............" << std::endl<<std::endl;
	PrintSurfaces(10);
	std::cout << "............" << std::endl<<std::endl;

}

void Model::PrintVertices()
{
	std::cout << "actual number of vertices: " << this->vertices.size() << std::endl;
	for (auto i = 0; i < this->vertices.size(); i++)
	{
		this->vertices[i].Print();
	}
}

void Model::PrintVertices(int number)
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

void Model::PrintSurfaces()
{
	std::cout << "actual number of surfaces: " << this->surfaces.size() << std::endl;
	for (auto i = 0; i < this->surfaces.size(); i++)
	{
		this->surfaces[i].Print();
	}
}

void Model::PrintSurfaces(int number)
{
	std::cout << "actual number of surfaces: " << this->surfaces.size() << std::endl;
	if (number <this->surfaces.size())
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

void Model::SetNumVertices(int number)
{
	this->num_vertices = number;
}

void Model::SetNumSurfaces(int number)
{
	this->num_surfaces = number;
}

int Model::GetNumVertices()
{
	return this->num_vertices;
}

int Model::GetNumSurfaces()
{
	return this->num_surfaces;
}

Vector3 Model::GetPosition() const
{
	return worldOffset;
}

void Model::SetPosition(Vector3& position)
{
	worldOffset = position;
}

std::vector<Vector3> Model::GetVertices()
{
	return this->vertices;
}

std::vector<Surface> Model::GetSurfaces()
{
	return this->surfaces;
}

void Model::LocalToWorld()
{
	Matrix4 m_localToWorld = Matrix4(1, 0, 0, this->worldOffset.GetX(),
									 0, 1, 0, this->worldOffset.GetY(),
									 0, 0, 1, this->worldOffset.GetZ(),
									 0, 0, 0, 1);
	Vector4 tempv;
	for (auto& v :vertices)
	{
		tempv = (m_localToWorld * Vector4(v));
		v.Set(tempv.GetX(), tempv.GetY(), tempv.GetZ());
	}
}

void Model::OnUpdate()
{
	//if (rotate)
	//{
	//	for (auto& v : vertices) {
	//		v.RotateY(degree);
	//	}
	//}
}




