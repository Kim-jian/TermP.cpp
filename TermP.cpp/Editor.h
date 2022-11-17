#pragma once
#include "View.h"
#include "fstream"
#include "string"
#include "vector"
using namespace std;

class Editor {
private:
	bool IsPageChange();
	int nowPage;
	int lastLine;
	fstream myfile;
	fstream tmpFile;
	string s;
	void arrangePage();
	vector<string> data;
	vector<string> book;
	void setPage();
	string stateMessage;
public:
	void terminal();
	bool IsBookExist;
	int getPage();
	vector<string> getBook();
	void setState(string msg);
	string getState();
	bool loadFile();
	bool makeFile();
	Editor();
	void prePage();
	void nextPage();
	void insert(vector<string> parameter);
	void del(vector<string> parameter);
	void change(vector<string> parameter);
	string search(string parameter);
};
