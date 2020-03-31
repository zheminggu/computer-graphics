//#include "Utils.h"

#include "Vector3.h"
#include "Vector4.h"
#include "Draw.h"
#include <Windows.h>
#include <gl\GL.h>
#include <iostream>
#include <fstream>
//#include "Math.h"

//using namespace OpenGLUtils;
//using namespace Vector;

void Draw::DrawLine(Vector3 startPosition, Vector3 endPosition) {
	//startPosition.Print();
	//endPosition.Print();
	//std::cout << "start position" << startPosition.GetX() << " " << startPosition.GetY();
	//std::cout << "end position" << endPosition.GetX() << " " << endPosition.GetY() << std::endl;

	glBegin(GL_LINE_STRIP);
	glVertex2f(startPosition.GetX(), startPosition.GetY());
	glVertex2f(endPosition.GetX(), endPosition.GetY());
	glEnd();
}


void ImageBufferToFile(Vector4 imageBuffer[SCREEN_HEIGHT][SCREEN_WEIGHT]) {
	std::string data[SCREEN_HEIGHT];
	std::ofstream outfile;
	outfile.open("afile.txt", std::ios::out | std::ios::binary);
	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < SCREEN_WEIGHT; j++)
		{
			if (imageBuffer[i][j].GetW() != 0) {
				/*imageBuffer[i][j].Print();*/
				data[i] += '1';
				//data[i][j] = 1;
			}
			else
			{
				data[i] += '0';
				//data[i][j] = 0;
			}
			//imageBuffer[i][j].Print();
		}
	}

	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		outfile << data[i] << "\n";
	}
	outfile << std::endl;
	outfile.close();

}

//bool finish_a_draw = false;
void Draw::DrawPoints(float imageBuffer[SCREEN_HEIGHT][SCREEN_WEIGHT][4]) {
	
	//glPointSize(5);
	glBegin(GL_POINTS);
	for (int i = 0; i <SCREEN_HEIGHT ; i++)
	{
		for (int j = 0; j < SCREEN_WEIGHT; j++)
		{
			//glPointSize(2.0);
			glColor3fv(imageBuffer[i][j]);
			glVertex2f((j-320) /320.f, (i-240) / 240.f);
		}
	}
	glEnd();

	
	/*if (!finish_a_draw)
	{
		ImageBufferToFile(imageBuffer);
		Debug::Log("finish a draw");

	}

	finish_a_draw = true;*/
}

void Draw::DrawPoints(int image[256][256][3])
{
	glBegin(GL_POINTS);
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			//glPointSize(2.0);
			glColor3fv((const float *)image[i][j]);
			glVertex2f((j - 320) / 320.f, (i - 240) / 240.f);
		}
	}
	glEnd();
}

