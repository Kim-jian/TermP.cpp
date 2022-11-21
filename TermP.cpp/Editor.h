#pragma once
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
	void arrangePage();
	vector<string> data;
	vector<string> book;
	void setPage();
	string stateMessage;
	bool IsBookExist;

public:
	bool BookExist();
	void terminal();
	int getPage();
	vector<string> getBook();
	void setState(string msg);
	string getState();
	bool loadFile();
	void makeFile();
	Editor();
	void prePage();
	void nextPage();
	void insert(vector<string> parameter);
	void del(vector<string> parameter);
	void change(vector<string> parameter);
	string search(string parameter);
};
