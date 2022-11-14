#pragma once
#include "Editor.h"
#include "View.h"

class Controller {
private:
	const char* lineSpliter = "-------------------------------------------------------------------------------------------";
	const char* menu = "n:다음페이지, p:이전페이지, i:삽입, d:삭제, c:변경, s:찾기, t:저장후종료";
	Editor model;
	int decide(std::string e);
	View sc;
	std::vector<string> book;
public:
	Controller();
	void run();
	int show();
};