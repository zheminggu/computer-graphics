#pragma once
#ifndef DEBUG_H
#define DEBUG_H
#define ObjectName(x) #x

#include <string>
#include <iostream>

class Debug
{
public:
	Debug();
	~Debug();

	static void Log(const std::exception& e);
	static void Log(const std::string& information);
	static void Log(const int number1, const int number2);
	template<typename T>
	inline static void Log(const std::string& information, const T number) {
		std::cout << information <<" " <<number<<std::endl;
	}
	template<typename T>
	inline static void Log(const T number) {
		std::cout << number << std::endl;
	}
	
	template<typename T>
		inline static void Log(const std::string& information1, const T number1, const std::string& information2, const T number2) {
		std::cout << information1 << " " <<number1 <<" " << information2<< " "<<number2 <<std::endl;
	}

	static void LogError(const std::string& errorInfo);
private:

};


#endif // !DEBUG_H
