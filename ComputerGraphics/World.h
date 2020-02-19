#pragma once

#ifndef WORLD_H
#define WORLD_H
#include "RenderModel.h"
#include "EdgeTable.h"
#include "Math.h"
class Camera;
class Model;
class RenderModel;
class ClippingPlane;
class Matrix4;
class Vector3;
class Vector4;
class EdgeTable;

class World {
public:
	World();
	~World();
	//Camera GetCamera();
	void LoadModel(Model& model);
	void LoadModel(Model& model, Vector3& offset);
	void LoadCamera(Camera& camera);
	void InitWorld();
	void PreRun();
	void Run();
	void SetCameraPosition(Vector3& position);
	Camera GetMainCamera();

	Vector4 hslToRgb(float h, float s, float l);
private:
	void BackFaceCulling();
	void NoBackFaceCulling();
	void ModelToView();
	void CalculateModelColor();
	void ViewToPrejection();
	void RegulateRenderModels();
	void SurfacesToEdgeTables();
	void CreateImage();

	void HSLtoRGBColor();

	//helping function
	void InitZBuffer();
	void InitImageBuffer();
	
private:
	std::vector<EdgeTable> edgeTables;
	Camera* mainCamera;
	std::vector<Camera> Cameras;
	std::vector<Model> Models;
	std::vector<RenderModel> RenderModels;


};
#endif // !WORLD_H
