#include "Debug.h"
//#include <fstream>
//#include <sstream>
//#include <string>


Debug::Debug()
{
}

Debug::~Debug()
{
}

void Debug::Log(const std::exception& e)
{
	std::cout << e.what() << std::endl;
}

void Debug::Log(const std::string& information)
{
	std::cout << information << std::endl;
}



void Debug::Log(const int number1, const int number2) {
	std::cout << number1 <<" " <<number2 << std::endl;
}



