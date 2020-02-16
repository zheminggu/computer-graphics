#pragma once
#ifndef SURFACE_H // include guard
#define SURFACE_H

#include <vector>
//#include <string>
//#include <iostream>

class Surface
{
private:
	std::vector<int> s;
public:
	Surface();
	void AddSurfacePoint(int index);
	std::vector<int> GetSurface();
	void Print();
};

#endif