//model class�̸�, ������ �޾ƿ���, pageManager���� �޾ƿ� ������ Bookȭ ��Ų��.
//�׸��� pageManager�� bookȭ�� ������ ��Ʈ���Ѵ�.
//book�� edit�ϱ� ���� vector<string>�� �ϳ� ������ �ִ´�.
//file�� edit�ϱ� ���� class, pageManager�� Controller�� ��ɿ� ���� �۵���Ų��.
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
				for (int i = 0; i < MAX_LEN-left+1; i++) {
					s += " ";
				}//���� �Է½� ���� �ٲ�
			}
			else  s += text + " ";
			//���๮�ڸ� ���鹮�ڷ� ��ü
		}
		//�� �������� s�� ��� test.txt�� �� �������� ó��
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
}//�� �������� data�� �� ���徿 ��� file�� ������ ����


string Editor::showBook() {
	vector<string> tmp = Editor::getBook();
	return Editor::getBook()[Editor::nowPage];
}

void Editor::nextPage() {
	if (Editor::nowPage+1 >= (int)(getBook().size())) {
		Editor::setState("This Page is Last Page Already.");
	}
	else {
		Editor::nowPage++;
		Editor::setState("This Page is " + to_string(nowPage + 1) + " Page.");
	}
}
void Editor::prePage() {
	if (Editor::nowPage - 1 <0) {
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
	string s = Editor::data[line-1+nowPage*20];
	if (strlen(s.c_str()) < 75) {
		for (int i = strlen(s.c_str()); i < MAX_LEN; i++) {
			s += " ";
		}
		s.replace(index, msg.size(), msg);
		int i = s.size();
		while (s[i]==' ') {
			s.erase(i);
			i--;
		}
		Editor::data[line - 1 + nowPage * 20] = s;
	}//������ ���� ������ ������
	else if (index+msg.size()>MAX_LEN) {
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
		for (int i = 0; i < s.size();j++) {
			string text = s.substr(i, MAX_LEN);
			i += text.size();
			if (isspace(s[i])) {
				i++;
			}
			data[line - 1 + j + nowPage * 20] = text;
		}
	}//�Է��� index���� ������ ���̰� ���� ������ ħ���� ���
	else {
		s.replace(index, msg.size(), msg);
		Editor::data[line - 1 + nowPage * 20] = s;
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
			}//���� �Է½� ���� �ٲ�
		}
		else  s += text + " ";
	}
	//���๮�ڸ� ���鹮�ڷ� ��ü
	//�� �������� s�� ��� test.txt�� �� �������� ó��
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
//���� ó���ؾ��� �� ������ �� ������ ���忡�� �����Ͼ�� segmant fault
//�������� �Ϸ�