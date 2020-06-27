// ComputerGraphics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <time.h>
#include <cmath>

//#include "Math.h"
//#include "Utils.h"
//using namespace FileUtils;
//using namespace Vector;
#include "File.h"
#include "Model.h"
#include "World.h"
#include "Camera.h"
#include "Vector3.h"
#include "Math.h"
#include "Texture.h"
//#include "glfw-3.3.bin.WIN32/include/GLFW/glfw3.h"

World world = World();
bool preview_mode = false;
bool lbutton_down = false;
bool scale_big = false;
bool scale_small = false;
bool change_light_direction = false;
double xpos = 0, ypos = 0;
double lastPosx = 0, lastPosy = 0;
double current_cameraPositionx=0, current_cameraPositiony=0;
double delta_x = 0;
double delta_y = 0;
int shadingType = CONSTANT_SHADING;
bool changeShadingType = false;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_1:
			shadingType = CONSTANT_SHADING;
			changeShadingType = true;
			break;
		case GLFW_KEY_2:
			shadingType = GOURAUD_SHADING;
			changeShadingType = true;
			break;
		case GLFW_KEY_3:
			shadingType = PHONG_SHADING;
			changeShadingType = true;
			break;
		case GLFW_KEY_E:
			preview_mode = true;
			break;
		case GLFW_KEY_D:
			preview_mode = false;
			break;
		case GLFW_KEY_W:
			scale_big = true;
			scale_small = false;
			break;
		case GLFW_KEY_S:
			scale_big = false;
			scale_small = true;
			break;
		case GLFW_KEY_A:
			scale_small = false;
			scale_big = false;
			break;
		case GLFW_KEY_R:
			change_light_direction = true;
			break;
		case GLFW_KEY_F:
			change_light_direction = false;
			break;
		default:
			break;
		}

	}

}

static void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		//std::cout << "xpos" << xpos << "ypos" << ypos << std::endl;

		if (GLFW_PRESS == action) {
			glfwGetCursorPos(window, &lastPosx, &lastPosy);
			lbutton_down = true;
		}
		else if (GLFW_RELEASE == action) {
			lbutton_down = false;
		}
	}
}

int main(void)
{
	Texture* n_tex = new Texture();
	Texture* n_ntex = new Texture();
	std::cout << "Tips" << "\n";
	std::cout << "input E to start preview mode" << "\n";
	std::cout << "input D to stop preview model" << "\n";
	std::cout << "input R to start light model" << "\n";
	std::cout << "input F to stop light model" << "\n";
	std::cout << "input W to move forward camera" << "\n";
	std::cout << "input S to move backward camera" << "\n";
	std::cout << "input A to stop move camera" << "\n";
	std::cout << "input 1 to change into constant shading model" << "\n";
	std::cout << "input 2 to change into gouraud shading model" << "\n";
	std::cout << "input 3 to change into phong shading model" << "\n";
	std::cout << "right click mouse to drag model" << "\n\n";

	std::cout << "to quick view default model please input " << "\n";
	std::cout << "Data\\Models\\batter-ball.d.txt" << "\n";
	std::cout << "Data\\Models\\cow.d.txt" << "\n\n";

	std::cout << "Please Input Model File Path" << std::endl;
	std::string file_path;
	std::getline(std::cin, file_path);
	//std::cin >> file_path;

	float distance = 15;
	bool show_FPS = false;
	int modelNumber = 6;
#pragma region Init World
	world.SetWorldColor(Vector3(255, 255, 255), 0.1f);
	//init the world

#pragma region Load Models
	auto file = File();
	Vector3 modelColor;
	auto model = file.OpenFile(file_path);

	Vector3 offset = Vector3(cos(2 * PI / modelNumber * 0) * 5, 0, sin(2 * PI / modelNumber * 0) * 5);
	modelColor = Vector3(std::rand() % 255, std::rand() % 255, std::rand() % 255);
	model.SetModelColor(modelColor, 1.f);
	n_tex->OpenTexture("Data/Textures/Pebbles_018_basecolor.jpg");
	n_ntex->OpenTexture("Data/Textures/Pebbles_018_normal.jpg");
	model.AddTexture(n_tex);
	model.AddNormalTexture(n_ntex);
	world.LoadModel(model, offset);

	offset = Vector3(cos(2 * PI / modelNumber * 1) * 5, 0, sin(2 * PI / modelNumber * 1) * 5);
	modelColor = Vector3(std::rand() % 255, std::rand() % 255, std::rand() % 255);
	model.SetModelColor(modelColor, 1.f);
	n_tex = new Texture;
	n_ntex = new Texture;
	n_tex->OpenTexture("Data/Textures/Metal_Plate_Sci-Fi_001_basecolor.jpg");
	n_ntex->OpenTexture("Data/Textures/Metal_Plate_Sci-Fi_001_normal.jpg");
	model.AddTexture(n_tex);
	model.AddNormalTexture(n_ntex);
	world.LoadModel(model, offset);

	offset = Vector3(cos(2 * PI / modelNumber * 2) * 5, 0, sin(2 * PI / modelNumber * 2) * 5);
	modelColor = Vector3(std::rand() % 255, std::rand() % 255, std::rand() % 255);
	model.SetModelColor(modelColor, 1.f);
	n_tex = new Texture;
	n_ntex = new Texture;
	n_tex->OpenTexture("Data/Textures/Pumpkin_001_basecolor.jpg");
	n_ntex->OpenTexture("Data/Textures/Pumpkin_001_normal.jpg");
	model.AddTexture(n_tex);
	model.AddNormalTexture(n_ntex);
	world.LoadModel(model, offset);

	offset = Vector3(cos(2 * PI / modelNumber * 3) * 5, 0, sin(2 * PI / modelNumber * 3) * 5);
	modelColor = Vector3(std::rand() % 255, std::rand() % 255, std::rand() % 255);
	model.SetModelColor(modelColor, 1.f);
	n_tex = new Texture;
	n_ntex = new Texture;
	n_tex->OpenTexture("Data/Textures/Roof_Tiles_Terracotta_003_basecolor.jpg");
	n_ntex->OpenTexture("Data/Textures/Roof_Tiles_Terracotta_003_normal.jpg");
	model.AddTexture(n_tex);
	model.AddNormalTexture(n_ntex);
	world.LoadModel(model, offset);

	offset = Vector3(cos(2 * PI / modelNumber * 4) * 5, 0, sin(2 * PI / modelNumber * 4) * 5);
	modelColor = Vector3(std::rand() % 255, std::rand() % 255, std::rand() % 255);
	model.SetModelColor(modelColor, 1.f);
	n_tex = new Texture;
	n_ntex = new Texture;
	n_tex->OpenTexture("Data/Textures/Terracota_Tiles_003_basecolor.jpg");
	n_ntex->OpenTexture("Data/Textures/Terracota_Tiles_003_normal.jpg");
	model.AddTexture(n_tex);
	model.AddNormalTexture(n_ntex);
	world.LoadModel(model, offset);

	offset = Vector3(cos(2 * PI / modelNumber * 5) * 5, 0, sin(2 * PI / modelNumber * 5) * 5);
	modelColor = Vector3(std::rand() % 255, std::rand() % 255, std::rand() % 255);
	model.SetModelColor(modelColor, 1.f);
	n_tex = new Texture;
	n_ntex = new Texture;
	n_tex->OpenTexture("Data/Textures/Snow_004_COLOR.jpg");
	n_ntex->OpenTexture("Data/Textures/Snow_004_NORM.jpg");
	model.AddTexture(n_tex);
	model.AddNormalTexture(n_ntex);
	world.LoadModel(model, offset);
#pragma endregion



	Vector3 lightDir = Vector3(0, 0, 10);
	Vector3 LightColor = Vector3(50, 158, 198);
	Light light = Light(lightDir, LightColor, 64, 1.f);
	world.LoadLight(light);

	Camera camera = Camera();
	Vector3 cameraPosition = Vector3(0, 0, distance);
	camera.SetPosition(cameraPosition);
	world.LoadCamera(camera);

	world.InitWorld();
	world.PreRun(shadingType);
#pragma endregion


	float x = 0;
	float now=0, previous=0;
	float delta_time=(float)glfwGetTime();

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow(640, 480, "Zheming Gu 6554 Computer Graphics II", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetMouseButtonCallback(window, mouse_callback);
	glfwSetKeyCallback(window, key_callback);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		now = glfwGetTime();
		delta_time = now - previous;
		//show FPS
		if (show_FPS)
		{
			std::cout << "FPS: " << 1 / delta_time << std::endl;
		}

		//hit E button to start preview mode hit D to end preview mode
		if (preview_mode) {
			//std::cout << "x: " <<x << std::endl;
			x = x + 0.5 * delta_time;
			Vector3 newCameraPosition = Vector3(distance * sin(x),0/* distance * cos(x)*/, distance * cos(x));
			world.SetCameraPosition(newCameraPosition);
			world.PreRun(shadingType);
		}
		
		//left mouse button down, then you could drag the model
		if (lbutton_down) {
			glfwGetCursorPos(window, &xpos, &ypos);
			delta_x =lastPosx-xpos;
			delta_y =lastPosy-ypos;
			delta_x =0.5* delta_time * delta_x;
			delta_y =0.5* delta_time * delta_y;
			//std::cout << "delta x: " << delta_x << " delta y: " << delta_y << std::endl;

			Vector3 newCameraPosition =Vector3(std::sin(current_cameraPositionx+ delta_x) * distance, 0, std::cos(current_cameraPositionx+delta_y) * distance);
			world.SetCameraPosition(newCameraPosition);
			world.PreRun(shadingType);

			current_cameraPositionx += delta_x;
			current_cameraPositionx += delta_y;
			lastPosx = xpos;
			lastPosy = ypos;
		}

		if (scale_big)
		{
			distance = distance- delta_time *10;
			Vector3 newCameraPosition = Vector3(0,0, distance);
			world.SetCameraPosition(newCameraPosition);
			world.PreRun(shadingType);
		}

		if (scale_small)
		{
			distance += delta_time *10;
			Vector3 newCameraPosition = Vector3(0, 0, distance);
			world.SetCameraPosition(newCameraPosition);
			world.PreRun(shadingType);
		}

		if (changeShadingType)
		{
			world.PreRun(shadingType);
			changeShadingType = false;
		}
		if (change_light_direction) {
			x = x + 0.5 * delta_time;
			Vector3 newLightPosition = Vector3(distance * sin(x), distance * cos(x), distance * cos(x));
			world.ChangeLightDirection(newLightPosition);
			world.PreRun(shadingType);
		}
		world.Run();
		previous = now;


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
		

	}

	glfwTerminate();
	return 0;
}

