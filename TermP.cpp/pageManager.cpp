//Editor의 sub model이다. book을 구성해준다.
#include "pageManager.h"
#define MAX_LEN 75
#define MAX_LINE 20


void pageManager::setContent(vector<string>& newContent) {
	pageManager::content = newContent;
}
void pageManager::setPage() {
	pageManager::book.clear();
	this->size = 0;
	int nowLine = 1;
	string present;
	for (vector<string>::iterator it = pageManager::content.begin(); it != pageManager::content.end(); it++) {
		if (nowLine > MAX_LINE) {
			pageManager::book.push_back(present);
			it--;
			present.clear();
			nowLine = 1;
		}
		else {
			string tmp;
			if (nowLine < 10) tmp = "  " + to_string(nowLine);
			else tmp = " " + to_string(nowLine);
			tmp += "| ";
			if (strcmp((*it).c_str()," ")==0) tmp += "\n";
			else tmp += *it;
			present += (tmp + "\n");
			this->size++;
			nowLine++;
			if (it+1 == content.end()) {
				pageManager::book.push_back(present);
				this->lastLine = nowLine-1;
				break;
			}
		}
	}
}//book 구성 완료
vector<string> pageManager::get_book() {
	return pageManager::book;
}

int pageManager::getLast() {
	return this->lastLine;
}

pageManager::pageManager() {
	size = 0;
	lastLine = 0;
}

int pageManager::getSize() {
	return this->size;
}