#include "Model.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdint>
#include "World.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "Draw.h"
#include "Debug.h"
#include "Texture.h"

float ZBuffer[SCREEN_HEIGHT][SCREEN_WEIGHT] = {};
float ImageBuffer[SCREEN_HEIGHT][SCREEN_WEIGHT][4] = {};


World::World()
{
	InitZBuffer();
}

World::~World()
{
}

// load model, apply local to world Matrix
void World::LoadModel(Model& model)
{
	Vector3 worldPosition = Vector3(0, 0, 0);
	model.SetPosition(worldPosition);
	this->Models.push_back(model);
}

void World::LoadModel(Model& model, Vector3& offset)
{
	Vector3 worldPosition = Vector3(offset);
	model.SetPosition(worldPosition);
	model.LocalToWorld();
	this->Models.push_back(model);
}

//load camera, apply local to world Matrix
void World::LoadCamera(Camera& camera)
{
	Matrix4 m_localToWorld = Matrix4();
	camera.LocalToWorld(m_localToWorld);
	this->Cameras.push_back(camera);
	if (/*mainCamera==NULL &&*/ this->Cameras.size()>=0)
	{
		mainCamera = Cameras[0];
	}
}

void World::LoadLight(Light& light)
{
	this->Lights.push_back(light);
}

void World::InitWorld() {

}

void World::PreRun(int shadingType)
{

	//choose one to run
	//NoBackFaceCulling();
	BackFaceCulling();
	InitVerticeVector();
	ModelToView();
	CalculateModelColor();
	ViewToPrejection();
	RegulateRenderModels();
	SurfacesToEdgeTables();
	CreateImage(shadingType);
	//HSLtoRGBColor();
}



void World::Run()
{
	for (auto model : Models) {
		model.OnUpdate();
	}
	/*for (auto& model : RenderModels) {
		model.DrawModel();
	}*/
	
	//std::cout << "world run once" << std::endl;
	Draw::DrawPoints(ImageBuffer);
}

void World::SetCameraPosition(Vector3& position)
{
	mainCamera.SetPosition(position);
}

Camera World::GetMainCamera()
{
	return mainCamera;
}

void World::ChangeLightDirection(Vector3& light_dir)
{
	for (auto& light :Lights)
	{
		light.SetLightDirection(light_dir);
	}
}

void World::BackFaceCulling()
{
	this->RenderModels.clear();
	RenderModel newRenderModel;
	Vector4 newVertice;
	Surface newSurface;
	std::vector<int> tempSurface;
	std::vector<Vector3> tempVertices;
	Vector3 CameraPosition = mainCamera.GetPosition();
	Vector3 V1, V2, Np, N;
	Vector3 modelColor;
	float k_d = 0;
	for (auto& model : Models) {
		newRenderModel = RenderModel();
		modelColor = model.GetModelColor();
		k_d = model.GetK_D();
		newRenderModel.SetModelColor(modelColor,k_d);
		tempVertices = model.GetVertices();
		for (auto& v : tempVertices) {
			newVertice = v.ToVector4();
			newRenderModel.AddVertices(newVertice);
		}
		for (auto& s : model.GetSurfaces()) {
			newSurface = s;
			//jugde if face is a back one 
			tempSurface = newSurface.GetSurface();
			
			V1 = tempVertices[tempSurface[1]] - tempVertices[tempSurface[0]];
			V2 = tempVertices[tempSurface[2]] - tempVertices[tempSurface[1]];
			Np = Vector3::Cross(V2, V1);
			N = CameraPosition - tempVertices[tempSurface[1]];
			if (Np * N >0)
			{
				newRenderModel.AddSurfaces(newSurface);
			}

		}
		this->RenderModels.push_back(newRenderModel);
	}
}

void World::NoBackFaceCulling()
{
	this->RenderModels.clear();
	RenderModel newRenderModel;
	Vector4 newVertice;
	Surface newSurface;
	Vector3 modelColor;
	float k_d = 0;
	for (auto& model : Models) {
		newRenderModel = RenderModel();
		modelColor = model.GetModelColor();
		k_d = model.GetK_D();
		newRenderModel.SetModelColor(modelColor,k_d);
		for (auto& v : model.GetVertices()) {
			newVertice = v.ToVector4();
			newRenderModel.AddVertices(newVertice);
		}
		for (auto& s : model.GetSurfaces()) {
			newSurface = s;
			newRenderModel.AddSurfaces(newSurface);
		}
		this->RenderModels.push_back(newRenderModel);
		//newRenderModel.PrintVertices();
	}
}

void World::InitVerticeVector()
{
	for (auto & model : RenderModels)
	{
		model.InitVerticeVector();
	}
}

void World::ModelToView()
{
	Matrix4 tempMat = mainCamera.GetMatView();
	//std::cout << "Apply Matrix world to view" << std::endl;
	//tempMat.Print();
	
	for (auto& model : RenderModels) {
		model.LeftProduct(tempMat);
		//model.PrintVertices();
	}

}

void World::CalculateModelColor() {
	
	//Vector3 LightDirection = Vector3(0, 0, 10);
	//Vector3 LightColor = Vector3(255, 255, 255);
	Vector3 CameraFront = mainCamera.GetFront();
	Vector3 modelColor;
	float k_d = 0;
	for (auto& model : RenderModels) {
		k_d = model.GetK_D();
		modelColor == model.GetModelColor();
		model.CalculateColor(CameraFront, Lights, this->worldColor, this->k_a);
	}
}

void World::ViewToPrejection()
{
	Matrix4 tempMat = mainCamera.GetMatPers();
	/*std::cout << "Apply Matrix view to prejection" << std::endl;
	tempMat.Print();*/
	for (auto& model : RenderModels) {
		model.LeftProduct(tempMat);
		//model.PrintVertices();
	}
}

void World::RegulateRenderModels() {
	for (auto& model: RenderModels)
	{
		model.RegulateModel();
	}
}

void World::SurfacesToEdgeTables()
{
	this->modelEdgeTables.clear();
	std::vector<EdgeTable> edge_table_model;
	for (auto& model : RenderModels) {

		edge_table_model = model.CreateEdgeTable();
		modelEdgeTables.push_back(edge_table_model);
	}
	//Debug::Log("over surface to edge Tables");
	//for (auto et : edgeTables)
	//{
	//	et.Print();
	//}
}

bool compareEdges_X(const ModelEdge& edge1, const ModelEdge& edge2) {
	if ((int)edge1.Xmin < (int)edge2.Xmin) return true;
	return false;
}

Texture* modelTexture;
Texture* modelNormalTexture;
void World::CreateImage(int shadingType)
{
	Vector3 CameraFront = mainCamera.GetFront();

	Vector4 constant_color;
	std::vector<ModelEdge> active_edge_table;
	int min_height = 0;
	int max_height = 0;
	int w_start = 0;
	int w_end = 0;
	Vector4 color_start; //color for gouraud shading
	Vector4 color_end;
	Vector3 vector_start;
	Vector3 vector_end;
	float z_start = 0;
	float z_end = 0;
	Vector4 color_slope_here;
	Vector3 vector_slope_here;
	Vector4 color_vector;// color for phone shading
	float z_slope_here = 0;
	InitZBuffer();
	InitImageBuffer();

	auto update_active_edge_table = [&](int h) {
		// sort active table
		active_edge_table.erase(std::remove_if(active_edge_table.begin(), active_edge_table.end(), [&](const ModelEdge& model) {
			return (int)model.Ymax <= h;
			}), active_edge_table.end());

		// update value
		for (auto& edge : active_edge_table)
		{
			edge.Xmin = edge.Xmin + edge.slope;
			edge.start_z = edge.start_z + edge.z_slope;
			if (shadingType == GOURAUD_SHADING)
			{
				edge.start_color.Add(edge.color_slope.GetX(),
									 edge.color_slope.GetY(),
									 edge.color_slope.GetZ(),
									 edge.color_slope.GetW());
			}
			else if (shadingType == PHONG_SHADING)
			{
				edge.start_vector.Add(edge.vector_slope.GetX(),
									  edge.vector_slope.GetY(), 
									  edge.vector_slope.GetZ());
			}

		}
	};

	Vector3 modelVector;
	Vector3 modelColor;
	float k_d = 0;
	int counter = 0;
	//int breaker = 0;
	for (auto& edgeTables : this->modelEdgeTables) {
		modelTexture = Models[counter].GetTexture();
		modelNormalTexture = Models[counter].GetNormalTexture();
		counter++;
		for (auto& et : edgeTables)
		{
			if (et.edge_list.size() == 0) continue;
			min_height = et.edge_list.begin()->first;
			for (auto& e : et.edge_list.rbegin()->second) {
				if (e.Ymax > max_height) {
					max_height = (int)e.Ymax;
				}
			}
			min_height = clamp(min_height, 0, Screen_Height);
			max_height = clamp(max_height, 0, Screen_Height);

			//for constant shading
			constant_color = et.edge_list.begin()->second[0].start_color;

			//for phong shading
			modelColor = et.GetModelColor();
			k_d = et.GetK_D();


			active_edge_table.clear();

			for (auto& h = min_height; h < max_height; h++)
			{
				//there are new edges in the edge list
				if (et.edge_list.count(h) == 1)
				{
					for (auto& edge : et.edge_list[h])
					{
						active_edge_table.push_back(edge);
					}
					update_active_edge_table(h);
					std::sort(active_edge_table.begin(), active_edge_table.end(), compareEdges_X);
				}
				else// no new edges in the edge list
				{
					//just update
					update_active_edge_table(h);

					std::sort(active_edge_table.begin(), active_edge_table.end(), compareEdges_X);
				}

				// in cased active edge table is null 
				if (active_edge_table.size() == 0)
				{
					continue;
				}

				for (auto i = 0; i < active_edge_table.size() - 1; i += 2)
				{
					w_start = (int)clamp(active_edge_table[i].Xmin, 0, Screen_Weight);
					w_end = (int)clamp(active_edge_table[i + 1].Xmin, 0, Screen_Weight);
					if (w_start == w_end) continue;

					z_start = active_edge_table[i].start_z;
					z_end = active_edge_table[i + 1].start_z;
					z_slope_here = (z_start - z_end) / (w_start - w_end);

					if (shadingType == CONSTANT_SHADING)
					{

						for (int w = w_start; w < w_end; w++)
						{
							z_start = z_start + z_slope_here;
							if (z_start < ZBuffer[h][w])
							{

								ImageBuffer[h][w][0] = constant_color.GetX() / 255.f;
								ImageBuffer[h][w][1] = constant_color.GetY() / 255.f;
								ImageBuffer[h][w][2] = constant_color.GetZ() / 255.f;
								ImageBuffer[h][w][3] = constant_color.GetW();

								ZBuffer[h][w] = z_start;
								//Debug::Log("now zbuffer[h][w] is", ZBuffer[h][w]);
								/*breaker++;
								if (breaker >5)
								{
									break;

								}*/

							}
						}
					}
					if (shadingType == GOURAUD_SHADING)
					{
						color_start = active_edge_table[i].start_color;
						color_end = active_edge_table[i + 1].start_color;
						color_slope_here = (color_start - color_end) / (const float)(w_start - w_end);

						//test
						//breaker = 0;
						for (int w = w_start; w < w_end; w++)
						{
							color_start = color_start + color_slope_here;
							z_start = z_start + z_slope_here;
							if (z_start < ZBuffer[h][w])
							{
								/*color_start.GetX();
								color_start.GetY();
								color_start.GetZ();
								color_start.GetW();*/
								//Debug::Log(h, w);
								ImageBuffer[h][w][0] = color_start.GetX() / 255.f;
								ImageBuffer[h][w][1] = color_start.GetY() / 255.f;
								ImageBuffer[h][w][2] = color_start.GetZ() / 255.f;
								ImageBuffer[h][w][3] = color_start.GetW();

								ZBuffer[h][w] = z_start;
								//Debug::Log("now zbuffer[h][w] is", ZBuffer[h][w]);
								/*breaker++;
								if (breaker >5)
								{
									break;

								}*/

							}
						}
					}
					else if (shadingType == PHONG_SHADING)
					{
						vector_start = active_edge_table[i].start_vector;
						vector_end = active_edge_table[i + 1].start_vector;
						vector_slope_here = (vector_start - vector_end) / (const float)(w_start - w_end);

						for (int w = w_start; w < w_end; w++)
						{
							vector_start = vector_start + vector_slope_here;
							z_start = z_start + z_slope_here;
							if (z_start < ZBuffer[h][w])
							{
								if (modelTexture!=NULL)
								{
									modelColor = modelTexture->GetColor(vector_start);
								}
								if (modelNormalTexture!= NULL)
								{
									modelVector = modelNormalTexture->GetNormal(vector_start);
									color_vector = RenderModel::CalculateColor(modelVector, CameraFront, Lights, worldColor, modelColor, k_a, k_d);

								}
								else
								{
									color_vector = RenderModel::CalculateColor(vector_start, CameraFront, Lights, worldColor, modelColor, k_a, k_d);
								}

								ImageBuffer[h][w][0] = color_vector.GetX() / 255.f;
								ImageBuffer[h][w][1] = color_vector.GetY() / 255.f;
								ImageBuffer[h][w][2] = color_vector.GetZ() / 255.f;
								ImageBuffer[h][w][3] = color_vector.GetW();

								ZBuffer[h][w] = z_start;

							}
						}
					}
				}
			}
		}
	}
	
}

void World::InitZBuffer()
{
	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < SCREEN_WEIGHT; j++)
		{
			ZBuffer[i][j] = 999;
		}
	}
}

void World::InitImageBuffer()
{
	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < SCREEN_WEIGHT; j++)
		{
			ImageBuffer[i][j][0] = 0;
			ImageBuffer[i][j][1] = 0;
			ImageBuffer[i][j][2] = 0;
			ImageBuffer[i][j][3] = 0;
		}
	}
}

