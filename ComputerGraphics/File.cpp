//#include "Utils.h"

//using namespace FileUtils;
#include "File.h"
//#include <string> 
//#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>

#include "Model.h"
#include "Vector3.h"
#include "Surface.h"
#include "Debug.h"

Model File::OpenFile() {
	std::ifstream ifs;
	ifs.open("C:\\Users\\zhemi\\Desktop\\GWU\\Graduate Term 2\\CG\\Data\\D files\\better-ball.d.txt");
	std::string line;
	Model model = Model();
	//get the first line to define how many vertices and surfaces
	std::getline(ifs, line);
	auto tempint = getInts(line);
	model.SetNumVertices(tempint[0]);
	model.SetNumSurfaces(tempint[1]);

	std::vector<float> tempfloats;
	//read vertices
	for (auto i = 0; i < model.GetNumVertices(); i++)
	{
		std::getline(ifs, line);
		tempfloats = getFloats(line);
		Vector3 point = Vector3(tempfloats[0],tempfloats[1],tempfloats[2]);
		model.AddVertices(point);
	}
	
	//read surfaces
	for (auto i = 0; i < model.GetNumSurfaces(); i++)
	{
		std::getline(ifs, line);
		Surface tempsurface = Surface();
		tempint = getInts(line);
		for (auto i = 1; i < tempint.size(); i++)
		{
			tempsurface.AddSurfacePoint(tempint[i]);
		}
		model.AddSurfaces(tempsurface);
	}

	//while (std::getline(ifs, line))
	//{
	//	if (i > 100) {
	//		break;
	//	}
	//	std::cout << line << std::endl;
	//	i++;
	//	//std::istringstream iss(line);
	//	//int a, b;
	//	//if (!(iss >> a >> b)) { break; } // error
	//	// process pair (a,b)
	//}

	ifs.close();
	return model;
}

Model File::OpenFile(std::string file_path) {
	//char* cstr = new char[file_path.length() -1 ];
	//const char* file_p = file_path.c_str();
	//for (int i = 0; i < file_path.length() - 1; i++)
	//{
	//	cstr[i] = file_p[i + 1];
	//}
	std::ifstream ifs;
	Model model = Model();
	Debug::Log(file_path);
	try
	{
		ifs.open(file_path);
		if (ifs.is_open()) {
			std::string line;
			//get the first line to define how many vertices and surfaces
			std::getline(ifs, line);
			auto tempint = getInts(line);
			model.SetNumVertices(tempint[0]);
			model.SetNumSurfaces(tempint[1]);

			std::vector<float> tempfloats;
			//read vertices
			for (auto i = 0; i < model.GetNumVertices(); i++)
			{
				std::getline(ifs, line);
				tempfloats = getFloats(line);
				Vector3 point = Vector3(tempfloats[0], tempfloats[1], tempfloats[2]);
				model.AddVertices(point);
			}

			//read surfaces
			for (auto i = 0; i < model.GetNumSurfaces(); i++)
			{
				std::getline(ifs, line);
				Surface tempsurface = Surface();
				tempint = getInts(line);
				for (auto i = 1; i < tempint.size(); i++)
				{
					tempsurface.AddSurfacePoint(tempint[i]);
				}
				model.AddSurfaces(tempsurface);
			}

			//while (std::getline(ifs, line))
			//{
			//	if (i > 100) {
			//		break;
			//	}
			//	std::cout << line << std::endl;
			//	i++;
			//	//std::istringstream iss(line);
			//	//int a, b;
			//	//if (!(iss >> a >> b)) { break; } // error
			//	// process pair (a,b)
			//}

			ifs.close();
		}
		else {
			Debug::Log("Error: cannot open file");
		}
		
	}
	catch (const std::exception& e)
	{
		Debug::Log(e);
	}

	
	return model;
}

void File::SaveFile() {

}


std::vector<float> File::getFloats(const std::string& s) {
	std::istringstream iss(s);
	std::string word;
	std::vector<float> result;

	size_t pos = 0;
	while (iss >> word) {
		try {
			float f = std::stof(word, &pos);
			if (pos == word.size()) {
				result.push_back(f);
			}
		}
		catch (std::invalid_argument const&) {
			// no part of word is a float
			continue;
		}
	}

	return result;
}

std::vector<int> File::getInts(const std::string& s) {
	std::istringstream iss(s);
	std::string word;
	std::vector<int> result;

	size_t pos = 0;
	while (iss >> word) {
		try {
			float f = std::stof(word, &pos);
			if (pos == word.size()) {
				result.push_back(f);
			}
		}
		catch (std::invalid_argument const&) {
			// no part of word is a float
			continue;
		}
	}

	return result;
}

