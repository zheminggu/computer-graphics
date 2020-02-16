#include "Model.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdint>
#include "World.h"
#include "Camera.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "Draw.h"
#include "Debug.h"

World::World()
{
	mainCamera = NULL;
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
	if (mainCamera==NULL && this->Cameras.size()>0)
	{
		mainCamera = &Cameras[0];
	}
}

void World::InitWorld() {

}

void World::PreRun()
{
	//choose one to run
	//NoBackFaceCulling();
	BackFaceCulling();
	ModelToView();
	ViewToPrejection();
	RegulateRenderModels();
	SurfacesToEdgeTables();
	CreateImage();
	//HSLtoRGBColor();
}



void World::Run()
{
	/*for (auto& model : RenderModels) {
		model.DrawModel();
	}*/
	
	//std::cout << "world run once" << std::endl;
	Draw::DrawPoints(ImageBuffer);
}

void World::SetCameraPosition(Vector3& position)
{
	mainCamera->SetPosition(position);
}

Camera World::GetMainCamera()
{
	return *mainCamera;
}


void World::BackFaceCulling()
{
	this->RenderModels.clear();
	RenderModel newRenderModel;
	Vector4 newVertice;
	Surface newSurface;
	std::vector<int> tempSurface;
	std::vector<Vector3> tempVertices;
	Vector3 CameraPosition = mainCamera->GetPosition();
	Vector3 V1, V2, Np, N;
	for (auto& model : Models) {
		newRenderModel = RenderModel();
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
	for (auto& model : Models) {
		newRenderModel = RenderModel();
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

void World::ModelToView()
{
	Matrix4 tempMat = mainCamera->GetMatView();
	//std::cout << "Apply Matrix world to view" << std::endl;
	//tempMat.Print();
	for (auto& model : RenderModels) {
		model.LeftProduct(tempMat);
		model.CalculateColor();
		//model.PrintVertices();
	}


}

void World::CalculateModelColor() {
	for (auto& model : RenderModels) {
		model.CalculateColor();
	}
}

void World::ViewToPrejection()
{
	Matrix4 tempMat = mainCamera->GetMatPers();
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
	
	this->edgeTables.clear();
	std::vector<EdgeTable> edge_table_model;
	for (auto& model : RenderModels) {

		edge_table_model = model.CreateEdgeTable();
		for (auto& et: edge_table_model)
		{
			edgeTables.push_back(et);
		}
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



void World::CreateImage()
{
	InitZBuffer();
	InitImageBuffer();
	std::vector<ModelEdge> active_edge_table;
	auto update_active_edge_table = [&](int h) {
		active_edge_table.erase(std::remove_if(active_edge_table.begin(), active_edge_table.end(), [&](const ModelEdge& model) {
			return (int)model.Ymax <= h;
			}), active_edge_table.end());
		for (auto& edge : active_edge_table)
		{
			edge.Xmin = edge.Xmin + edge.slope;
			edge.start_color->Set((*edge.start_color + *edge.color_slope).GetX(),
				(*edge.start_color + *edge.color_slope).GetY(),
				(*edge.start_color + *edge.color_slope).GetZ(),
				(*edge.start_color + *edge.color_slope).GetW());
			edge.start_z = edge.start_z + edge.z_slope;
		}
	};
	int min_height = 0;
	int max_height = 0;
	int w_start = 0;
	int w_end = 0;
	Vector4 color_start;
	Vector4 color_end;
	float z_start = 0;
	float z_end = 0;
	Vector4 color_slope_here;
	float z_slope_here;
	for (auto& et :this->edgeTables)
	{
		min_height = et.edge_list.begin()->first;
		for (auto& e : et.edge_list.rbegin()->second) {
			if (e.Ymax > max_height) {
				max_height = (int)e.Ymax;
			}
		}
		active_edge_table.clear();

		for (auto& h = min_height; h < max_height; h++)
		{
			if (et.edge_list.count(h)==1)
			{
				for (auto& edge : et.edge_list[h])
				{
					//ModelEdge newModelEdge = ModelEdge((int)edge.height, edge.Ymax, edge.Xmin, edge.slope, *edge.start_color, *edge.color_slope, edge.start_z, edge.z_slope);
					active_edge_table.push_back(edge);
				}
				update_active_edge_table(h);
				std::sort(active_edge_table.begin(), active_edge_table.end(), compareEdges_X);
			}
			else
			{
				update_active_edge_table(h);
				
				std::sort(active_edge_table.begin(), active_edge_table.end(), compareEdges_X);
			}
			if (active_edge_table.size()==0)
			{
				continue;
			}
			for (auto i = 0; i < active_edge_table.size()-1; i+=2)
			{
				w_start =clamp((int) active_edge_table[i].Xmin,0, Screen_Weight);
				w_end = clamp((int)active_edge_table[i + 1].Xmin,0, Screen_Weight);
				color_start = *active_edge_table[i].start_color;
				color_end = *active_edge_table[i + 1].start_color;
				z_start = active_edge_table[i].start_z;
				z_end = active_edge_table[i + 1].start_z;
				if (w_start == w_end) continue;
				color_slope_here = (color_start - color_end) / (const float)(w_start - w_end);
				z_slope_here = (z_start - z_end) / (w_start - w_end);
				for (int w = w_start; w < w_end; w++)
				{
					color_start = color_start + color_slope_here;
					z_start = z_start + z_slope_here;
					if (z_start<ZBuffer[h][w])
					{
						/*color_start.GetX();
						color_start.GetY();
						color_start.GetZ();
						color_start.GetW();*/
						//Debug::Log(h, w);
						ImageBuffer[h][w].Set(color_start.GetX(), color_start.GetY(), color_start.GetZ(), color_start.GetW());

	
						ZBuffer[h][w] = z_start;
						//Debug::Log("now zbuffer[h][w] is", ZBuffer[h][w]);
					}
				}
			}
		}

	}
	//Debug::Log("finish print");
}

void World::HSLtoRGBColor() {
	Vector4 RGBcolor;

	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < SCREEN_WEIGHT; j++)
		{
			//glPointSize(2.0);
			RGBcolor = hslToRgb(ImageBuffer[i][j].GetX(), ImageBuffer[i][j].GetY(), ImageBuffer[i][j].GetZ());
			ImageBuffer[i][j].Set(RGBcolor.GetX() / 255.f, RGBcolor.GetY() / 255.f, RGBcolor.GetZ() / 255.f,255);
			/*if (RGBcolor.GetX()!=0)
			{
				Debug::Log("here");
				ImageBuffer[i][j].Print();
			}*/
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
			ImageBuffer[i][j].Zero();
		}
	}
}


/**
 * Converts an HSL color value to RGB. Conversion formula
 * adapted from http://en.wikipedia.org/wiki/HSL_color_space.
 * Assumes h, s, and l are contained in the set [0, 1] and
 * returns r, g, and b in the set [0, 255].
 *
 * @param   {number}  h       The hue
 * @param   {number}  s       The saturation
 * @param   {number}  l       The lightness
 * @return  {Array}           The RGB representation
 */
Vector4 World::hslToRgb(float h, float s, float l) {
	Vector4 rgb;
	float r, g, b;

	if (s == 0) {
		r = g = b = l; // achromatic
	}
	else {
		auto hue2rgb = [](float p, float q, float t) {
			if (t < 0) t += 1;
			if (t > 1) t -= 1;
			if (t < 1 / 6) return p + (q - p) * 6 * t;
			if (t < 1 / 2) return q;
			if (t < 2 / 3) return p + (q - p) * (2 / 3 - t) * 6;
			return p;
		};

		float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
		float p = 2 * l - q;
		r = hue2rgb(p, q, h + 1 / 3);
		g = hue2rgb(p, q, h);
		b = hue2rgb(p, q, h - 1 / 3);
	}

	return Vector4(round(r * 255), round(g * 255), round(b * 255), 255);
}


