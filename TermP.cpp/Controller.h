#pragma once
#include "Editor.h"
#include "View.h"

class Controller {
private:
	const char* lineSpliter = "-------------------------------------------------------------------------------------------";
	const char* menu = "n:����������, p:����������, i:����, d:����, c:����, s:ã��, t:����������";
	Editor model;
	int decide(std::string e);
	int page;
	View sc;
	std::vector<string> book;
public:
	void run();
	int show();
};