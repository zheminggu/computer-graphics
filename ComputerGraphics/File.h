#pragma once
#ifndef FILE_H // include guard
#define FILE_H

#include <string> 
#include <vector>
class Model;
class File
{
private:
	std::string filename;
public:
	Model OpenFile();
	Model OpenFile(std::string file_path);
	void SaveFile();
private:
	std::vector<float> getFloats(const std::string& s);
	std::vector<int> getInts(const std::string& s);
};

#endif