#pragma once
#include "vector"
#include "string"
using namespace std;

class pageManager {
private:
	int size;
	int lastLine;
	vector<string> content;
	vector<string> book;
public:
	pageManager();
	void setContent(vector<string>& newContent);
	void setPage();
	int getLast();
	vector<string> get_book();
};