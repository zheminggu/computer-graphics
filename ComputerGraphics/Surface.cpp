#include "Surface.h"
#include <iostream>
#include <string>

Surface::Surface() {
	std::vector<int> tempvec;
	Surface::s = tempvec;
}

void Surface::AddSurfacePoint(int index) {
	Surface::s.push_back(index-1);
}

std::vector<int> Surface::GetSurface() {
	return s;
}

void Surface::Print()
{
	std::string result = "";
	for (auto i = 0; i < this->s.size(); i++)
	{
		result = result + std::to_string(s[i])+" ";
	}
	std::cout << result << std::endl;
}
