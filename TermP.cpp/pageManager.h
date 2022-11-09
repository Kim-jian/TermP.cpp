#pragma once
#include "vector"
#include "string"
using namespace std;

class pageManager {
private:
	int size;
	vector<string> content;
	vector<string> book;
public:
	pageManager();
	void setContent(vector<string>& newContent);
	void setPage();
	vector<string> get_book();
};