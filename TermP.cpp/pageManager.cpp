#include "pageManager.h"
#define MAX_LEN 20
#define MAX_LINE 75


void pageManager::setContent(vector<string>& newContent) {
	pageManager::content = newContent;
}
void pageManager::setPage() {
	int nowLen = 1;
	string present;
	for (vector<string>::iterator it = pageManager::content.begin(); it != pageManager::content.end(); it++) {
		if (nowLen > MAX_LEN) {
			pageManager::book.push_back(present);
			present.clear();
			nowLen = 1;
		}
		else {
			string tmp;
			if (nowLen < 10) tmp = "  " + to_string(nowLen);
			else tmp = " " + to_string(nowLen);
			tmp += "| ";
			if (strcmp((*it).c_str()," ")==0) tmp += "\n";
			else tmp += *it;
			present += (tmp + "\n");
			nowLen++;
			if (it+1 == content.end()) {
				pageManager::book.push_back(present);
				size++;
				break;
			}
		}
	}
}//book 구성 완료
vector<string> pageManager::get_book() {
	return pageManager::book;
}
pageManager::pageManager() {
	size = 0;
}