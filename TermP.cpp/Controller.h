#pragma once
#include "Editor.h"
#include "View.h"

class Controller {
private:
	const char* lineSpliter = "-------------------------------------------------------------------------------------------";
	const char* menu = "n:����������, p:����������, i:����, d:����, c:����, s:ã��, t:����������";
	Editor model;
	int decide(std::string e);
	View sc;
	std::vector<string> book;
public:
	Controller();
	void run();
	int show();
};