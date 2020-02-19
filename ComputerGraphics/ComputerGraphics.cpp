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
//#include "glfw-3.3.bin.WIN32/include/GLFW/glfw3.h"

World world = World();
bool preview_mode = false;
bool lbutton_down = false;
double xpos = 0, ypos = 0;
double lastPosx = 0, lastPosy = 0;
double current_cameraPositionx=0, current_cameraPositiony=0;
double delta_x = 0;
double delta_y = 0;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_E && action == GLFW_PRESS) {
		preview_mode = true;
	}
	else if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		preview_mode = false;
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
	//std::cout << "please input file path" << std::endl;
	//std::string file_path;
	////std::cin >> file_path;
	//std::getline(std::cin,file_path);

	//open file
	auto file = File();
	auto model = file.OpenFile(/*file_path*/);
	model.PrintModelInfo();
	Camera camera =Camera();
	world.LoadCamera(camera);
	world.LoadModel(model);
	Vector3 offset = Vector3(10, 0, 0);
	world.LoadModel(model,offset);
	//ready to run
	world.InitWorld();
	world.PreRun();
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
		//std::cout << "FPS: " << 1 / delta_time << std::endl;

		//hit E button to start preview mode hit D to end preview mode
		if (preview_mode) {
			//std::cout << "x: " <<x << std::endl;
			x = x + 0.5 * delta_time;
			Vector3 newCameraPosition = Vector3(20 * sin(x), 0, 20 * cos(x));
			world.SetCameraPosition(newCameraPosition);
			world.PreRun();
		}
		
		//left mouse button down, then you could drag the model
		if (lbutton_down) {
			glfwGetCursorPos(window, &xpos, &ypos);
			delta_x =lastPosx-xpos;
			delta_y =lastPosy-ypos;
			delta_x =0.5* delta_time * delta_x;
			delta_y =0.5* delta_time * delta_y;
			//std::cout << "delta x: " << delta_x << " delta y: " << delta_y << std::endl;

			Vector3 newCameraPosition =Vector3(std::sin(current_cameraPositionx+ delta_x) * 10, /*10*(ypos-240)/240*/0, std::cos(current_cameraPositionx+delta_y) * 10);
			world.SetCameraPosition(newCameraPosition);
			world.PreRun();

			current_cameraPositionx += delta_x;
			current_cameraPositionx += delta_y;
			lastPosx = xpos;
			lastPosy = ypos;
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

