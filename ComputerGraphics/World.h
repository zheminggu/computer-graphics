#pragma once

#ifndef WORLD_H
#define WORLD_H
#include "RenderModel.h"
#include "EdgeTable.h"
#include "Math.h"
#include "Camera.h"
#include "Light.h"

class Camera;
class Model;
class RenderModel;
class ClippingPlane;
class Matrix4;
class Vector3;
class Vector4;
class EdgeTable;
class Light;

class World {
public:
	World();
	~World();
	//Camera GetCamera();
	void LoadModel(Model& model);
	void LoadModel(Model& model, Vector3& offset);
	void LoadCamera(Camera& camera);
	void LoadLight(Light& light);
	void InitWorld();
	void PreRun(int shadingType);
	void Run();
	void SetCameraPosition(Vector3& position);
	Camera GetMainCamera();
	void ChangeLightDirection(Vector3& light_dir);
	inline void SetWorldColor(Vector3 color, float k_a) { this->worldColor = Vector3(color); this->k_a = k_a; }
private:
	void BackFaceCulling();
	void NoBackFaceCulling();
	void InitVerticeVector();
	void ModelToView();
	void CalculateModelColor();
	void ViewToPrejection();
	void RegulateRenderModels();
	void SurfacesToEdgeTables();
	void CreateImage(int shadingType);

	//helping function
	void InitZBuffer();
	void InitImageBuffer();
	
private:
	std::vector<EdgeTable> edgeTables;
	Camera mainCamera;
	std::vector<Camera> Cameras;
	std::vector<Model> Models;
	std::vector<Light> Lights;
	std::vector<RenderModel> RenderModels;
	Vector3 worldColor;
	float k_a;
};
#endif // !WORLD_H
