#pragma once

#ifndef MATH_H // include guard
#define MATH_H
#define SCREEN_WEIGHT 640
#define SCREEN_HEIGHT 480
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
#endif /* MATH_H */
