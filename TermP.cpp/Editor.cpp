
#include "Editor.h"

#define MAX_LEN 20
#define MAX_LINE 75

Editor::Editor() {
	Editor::nowPage = 0;
	Editor::stateMessage = "This Page is 1 Page.";
}

string Editor::getState() {
	return stateMessage;
}

Editor::~Editor() {
	Editor::myfile.close();
}
void Editor::makePage() {
	Editor::page.setContent(data);
	Editor::page.setPage();
}
vector<string> Editor::getBook() {
	return Editor::page.get_book();
}
bool Editor::loadFile() {
	Editor::myfile.open("test.txt");
	if (Editor::myfile.is_open()) {
		return true;
	}
	return false;
}
bool Editor::makeFile() {
	if (Editor::myfile.is_open()) {
		Editor::s.clear();
		while (!Editor::myfile.eof()) {
			string text;
			getline(myfile, text);
			if (strcmp(text.c_str(), "") == 0) {
				int left = s.size() % MAX_LINE;
				for (int i = 0; i < MAX_LINE-left+1; i++) {
					s += " ";
				}//개행 입력시 한줄 바꿈
			}
			else  s += text + " ";
			//개행문자를 공백문자로 대체
		}
		//이 시점에서 s에 모든 test.txt가 한 문장으로 처리
		for (int i = 0; i < s.size();) {
			string text = s.substr((int)i, (int)MAX_LINE);
			i += text.size();
			if (isspace(s[i])) {
				i++;
			}
			data.push_back(text);
		}
		s.clear();
		Editor::makePage();
		return true;
	}
	return false;
}


string Editor::showBook() {
	vector<string> tmp = Editor::getBook();
	return Editor::getBook()[Editor::nowPage];
}

void Editor::nextPage() {
	if (Editor::nowPage+1 >= (int)(getBook().size())) {
		Editor::stateMessage = "This Page is Last Page Already.";
	}
	else {
		Editor::nowPage++;
		Editor::stateMessage = "This Page is " + to_string(nowPage + 1) + " Page.";
	}
}
void Editor::prePage() {
	if (Editor::nowPage - 1 <0) {
		Editor::stateMessage = "This Page is First Page Already.";
	}
	else {
		Editor::nowPage--;
		Editor::stateMessage = "This Page is " + to_string(nowPage + 1) + " Page.";
	}
}