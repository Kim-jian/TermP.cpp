
#pragma once
#include "iostream"
#include "vector"
#include "string"
#include "sstream"

class View {
public:
	void output(std::string msg);
	void outputLine(std::string msg);
	std::string inputString();
};