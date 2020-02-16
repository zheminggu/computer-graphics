#pragma once
#ifndef DRAW_H // include guard
#define DRAW_H

#include "Math.h"

class Vector3;
class Vector4;

class Draw {
public:
	static void DrawLine(Vector3 startPosition, Vector3 endPosition);
	static void DrawPoints(Vector4 imageBuffer[SCREEN_HEIGHT][SCREEN_WEIGHT]);

	

};
#endif