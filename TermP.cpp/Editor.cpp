//model class이며, 파일을 받아오고, pageManager에게 받아온 파일을 Book화 시킨다.
//그리고 pageManager의 book화된 파일을 컨트롤한다.
//book을 edit하기 위한 vector<string>을 하나 가지고 있는다.
//file을 edit하기 위한 class, pageManager를 Controller의 명령에 따라 작동시킨다.
#include "Editor.h"

#define MAX_LEN 75
#define MAX_LINE 20

Editor::Editor() {
	Editor::nowPage = 0;
	Editor::stateMessage = "This Page is 1 Page.";
}

void Editor::setState(string msg) {
	this->stateMessage = msg;
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
				int left = s.size() % MAX_LEN;
				for (int i = 0; i < MAX_LEN - left + 1; i++) {
					s += " ";
				}//개행 입력시 한줄 바꿈
			}
			else  s += text + " ";
			//개행문자를 공백문자로 대체
		}
		//이 시점에서 s에 모든 test.txt가 한 문장으로 처리
		for (int i = 0; i < s.size();) {
			string text = s.substr((int)i, (int)MAX_LEN);
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
}//이 시점에서 data는 한 문장씩 끊어서 file을 가지고 있음

string Editor::caseLast() {
	int i = data.size()- MAX_LINE;
	int j = 1;
	string s = "  "+to_string(j++) + "| "+this->data[i++]+"\n";
	while (i < data.size()) {
		if(j<10) s+= "  " + to_string(j++) + "| " + this->data[i++] + "\n";
		else s+= " "+to_string(j++) + "| " + this->data[i++] + "\n";
	}
	return s;
}

string Editor::showBook() {
	vector<string> tmp = Editor::getBook();
	switch (tmp.size() > 0) {
	case 1 :
		if (nowPage == this->getBook().size()-1) {
			return caseLast();
		}
		return tmp[Editor::nowPage];
	case 0: 
		return "";
	}
}

void Editor::nextPage() {
	if (Editor::nowPage + 1 >= (int)(getBook().size())) {
		Editor::setState("This Page is Last Page Already.");
	}
	else {
		Editor::nowPage++;
		Editor::setState("This Page is " + to_string(nowPage + 1) + " Page.");
	}
}
void Editor::prePage() {
	if (Editor::nowPage - 1 < 0) {
		Editor::setState("This Page is First Page Already.");
	}
	else {
		Editor::nowPage--;
		Editor::setState("This Page is " + to_string(nowPage + 1) + " Page.");
	}
}
void Editor::insert(vector<string> e) {
	int line;
	string msg;
	int index;
	try {
		line = stoi(e[0]);
		int MAX = MAX_LINE;
		if (data.size() == 0) {
			MAX = 1;
		}
		else if (nowPage + 1 == (getBook().size())) {
			MAX = page.getLast();
		}
		if (line > MAX || line <= 0) {
			throw out_of_range("Line parameters are not appropriate.");
		}
	}
	catch (std::invalid_argument e) {
		Editor::setState("Line must be an integer type.");;
		return;
	}
	catch (std::out_of_range e) {
		Editor::setState(e.what());
		return;
	}
	try {
		index = stoi(e[1]);
		msg = e[2];
		if (index <= 0 || index > MAX_LEN) {
			throw std::out_of_range("Index parameters are not appropriate.");
		}
		index--;
	}
	catch (std::invalid_argument e) {
		Editor::setState("Index must be an integer type.");
		return;
	}
	catch (std::out_of_range e) {
		Editor::setState(e.what());
		return;
	}
	if (data.size() == 0) {
		data.push_back(msg);
	}
	else {
		string s = Editor::data[line - 1 + nowPage * 20];
		if (strlen(s.c_str()) < 75) {
			for (int i = strlen(s.c_str()); i < MAX_LEN; i++) {
				s += " ";
			}
			s.replace(index, msg.size(), msg);
			int i = s.size()-1;
			while (s[i] == ' ') {
				s.erase(i);
				i--;
			}
			Editor::data[line - 1 + nowPage * 20] = s;
		}//마지막 쪽의 마지막 문장임
		else if (index + msg.size() > MAX_LEN) {
			int size = index + msg.size();
			int i = 0;
			bool over = false;
			while (size > MAX_LEN) {
				s += (data[line + i + nowPage * 20]);
				i++;
				if (line + i + nowPage * 20 > data.size()) {
					size -= data[data.size()].size();
					over = true;
					break;
				}
				size -= MAX_LEN;
			}
			if (over) {
				while (size > 0) {
					s += " ";
					if (s.size() % MAX_LEN == 0) {
						s += "\n";
					}
					size--;
				}
			}
			s.replace(index, msg.size(), msg);
			int j = 0;
			for (int i = 0; i < s.size(); j++) {
				string text = s.substr(i, MAX_LEN);
				i += text.size();
				if (isspace(s[i])) {
					i++;
				}
				data[line - 1 + j + nowPage * 20] = text;
			}
		}//입력한 index부터 문자의 길이가 다음 문장을 침범할 경우
		else {
			s.replace(index, msg.size(), msg);
			Editor::data[line - 1 + nowPage * 20] = s;
		}
	}
	Editor::arrangePage();
	Editor::setState("Insert function Complete.");
}

void Editor::arrangePage() {
	string text;
	for (vector<string>::iterator it = Editor::data.begin(); it != data.end(); it++) {
		text = *it;
		if (strcmp(text.c_str(), "") == 0) {
			int left = s.size() % MAX_LEN;
			for (int i = 0; i < MAX_LEN - left + 1; i++) {
				s += " ";
			}//개행 입력시 한줄 바꿈
		}
		else  s += text + " ";
	}
	//개행문자를 공백문자로 대체
	//이 시점에서 s에 모든 test.txt가 한 문장으로 처리
	Editor::data.clear();
	for (int i = 0; i < s.size();) {
		string text = s.substr((int)i, (int)MAX_LEN);
		i += text.size();
		if (isspace(s[i])) {
			i++;
		}
		data.push_back(text);
	}
	Editor::s.clear();
	Editor::makePage();
}

void Editor::del(vector<string> parameter) {
	int line;
	int index;
	int byte;
	try {
		line = stoi(parameter[0]);
		int MAX = MAX_LINE;
		if (nowPage + 1 == (getBook().size())) {
			MAX = page.getLast();
		}
		if (line > MAX || line <= 0) {
			throw out_of_range("Line parameters are not appropriate.");
		}
	}
	catch (std::invalid_argument e) {
		Editor::setState("Line must be an integer type.");;
		return;
	}
	catch (std::out_of_range e) {
		Editor::setState(e.what());
		return;
	}
	try {
		index = stoi(parameter[1]);
		if (index <= 0 || index > MAX_LEN) {
			throw std::out_of_range("Index parameters are not appropriate.");
		}
	}
	catch (std::invalid_argument e) {
		Editor::setState("Index must be an integer type.");
		return;
	}
	catch (std::out_of_range e) {
		Editor::setState(e.what());
		return;
	}
	try {
		byte = stoi(parameter[2]);
		int totalSize;
		totalSize = (this->page.getSize() - nowPage * MAX_LINE - (line - 1)) * MAX_LEN;  //남은 line 수*한 라인당 바이트
		totalSize -= index;
		if (byte <= 0 || byte > totalSize) {
			throw out_of_range("Byte parameters are not appropriate.(Bound Out)");
		}
	}
	catch (std::invalid_argument e) {
		Editor::setState("Byte must be an integer type.");
		return;
	}
	catch (std::out_of_range e) {
		Editor::setState(e.what());
		return;
	}
	string tmp;
	for (vector<string>::iterator it = data.begin(); it != data.end(); it++) {
		tmp += (*it);
	}
	tmp.erase(index - 1 + (nowPage)*MAX_LEN * MAX_LINE + (line - 1) * MAX_LEN, byte);//현재 시점 계산식 참고
	data.clear();
	if (strcmp(tmp.c_str(), "")) {
		for (int i = 0; i < tmp.size();) {
			string text = tmp.substr((int)i, (int)MAX_LEN);
			i += text.size();
			if (isspace(tmp[i])) {
				i++;
			}
			data.push_back(text);
		}
	}
	Editor::arrangePage();
	Editor::setState("Delete function Complete.");
}

void Editor::change(vector<string> parameter) {
	
}