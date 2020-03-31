#pragma once

#ifndef MATH_H // include guard
#define MATH_H
#define SCREEN_WEIGHT 640
#define SCREEN_HEIGHT 480

//shading types
#define CONSTANT_SHADING 0
#define GOURAUD_SHADING 1
#define PHONG_SHADING 2

#include <cmath>
#include "Debug.h"

const float PI = (float)std::acos(-1);
const float Screen_Height = 480;
const float Screen_Weight = 640;

inline float clamp(float  number, float min, float max) {
	if (number < min) {
		//Debug::Log("clamping max",number);
		number = min;
	}
	if (number > max) {
		//Debug::Log("clamping max", number);
		number = max;
	}
	return number;
}

inline float lerp(float start, float end, float percent) {
	return start + percent * (end - start);
}

#endif /* MATH_H */
