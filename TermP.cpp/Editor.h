#pragma once
#include "View.h"
#include "fstream"
#include "string"
#include "vector"
#include "pageManager.h"
using namespace std;

class Editor {
private:
	int nowPage;
	fstream myfile;
	string s;
	void makePage();
	void arrangePage();
	vector<string> data;
	pageManager page;
	string stateMessage;
public:
	vector<string> getBook();
	string showBook();
	void setState(string msg);
	string getState();
	bool loadFile();
	bool makeFile();
	Editor();
	~Editor();
	void prePage();
	void nextPage();
	void insert(vector<string> parameter);
};
