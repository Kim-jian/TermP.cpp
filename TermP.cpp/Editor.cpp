//model class�̸�, ������ �޾ƿ���, pageManager���� �޾ƿ� ������ Bookȭ ��Ų��.
//book�� edit�ϱ� ���� vector<string>�� �ϳ� ������ �ִ´�.
#include "Editor.h"

#define MAX_LEN 75
#define MAX_LINE 20


Editor::Editor() {
	Editor::nowPage = 0;
	Editor::IsBookExist = false;
	Editor::stateMessage = "This Page is 1 Page.";
	Editor::lastLine = 0;
}

bool Editor::BookExist() {
	return this->IsBookExist;
}

int Editor::getPage() {
	return this->nowPage;
}

void Editor::setState(string msg) {
	this->stateMessage = msg;
}


string Editor::getState() {
	return stateMessage;
}





void Editor::setPage() {
	book.clear();
	ofstream otempo;
	otempo.open("tmpFile.txt",ios::out);
	for (vector<string>::iterator it = data.begin(); it != data.end(); it++) {
		otempo << (*it) + "\n";
	}
	otempo.close();
	int nowLine = 1;
	string present;
	string page;
	ifstream tempo;
	tempo.open("tmpFile.txt", ifstream::in);
	while (getline(tempo, present)) {
		if (nowLine < 10) page += "  " + to_string(nowLine);
		else page += " " + to_string(nowLine);
		page += "| ";
		page += present;
		page += "\n";
		nowLine++;
		present.clear();
		if (nowLine > MAX_LINE) {
			book.push_back(page);
			page.clear();
			nowLine = 1;
		}
	}
	tempo.close();
	if (page.size() != 0) {//������ ������ �籸��
		page.clear();
		nowLine = 1;
		for (int j = 0; j < MAX_LINE; j++) {
			if (nowLine < 10) page += "  " + to_string(nowLine);
			else page += " " + to_string(nowLine);
			page += "| ";
			if (data.size() < MAX_LINE) {
				page += data[j];
				if (j + 1 >= data.size()) {
					break;
				}
			}
			else page += data[data.size() - MAX_LINE+j];
			page += "\n";
			nowLine++;
		}
		book.push_back(page);
	}
	if (book.size() > 0) Editor::IsBookExist = true;
}//book ���� �Ϸ�  book�� �����ϴ� �Լ��̴�.

#pragma warning(push)
#pragma warning(disable: 6031)
bool Editor::IsPageChange() {
	return (book.size() <= nowPage) ? true: false;
}
#pragma warning(pop)
//���� ������ page�� �з� book�� size�� ��ȭ�� Ÿ�����ϴ�
//nowPage�� ��ĭ �پ�� �Ѵ�. �� check�� ���� �Լ�

bool Editor::loadFile() {
	Editor::myfile.open("test.txt");
	if (Editor::myfile.is_open()) {
		ifstream tmp("test.txt");
		string s;
		getline(tmp, s);
		if (s == "") {
			tmp.close();
			return false;
		}
		tmp.close();
		Editor::makeFile();
		return true;
	}
	return false;
}
void Editor::makeFile() {
		string s;
		while (!Editor::myfile.eof()) {
			string text;
			getline(myfile, text);
			s += text;
		}
		//�� �������� s�� ��� test.txt�� �� �������� ó��
		for (int i = 0; i < s.size();) {
			string text = s.substr(i, MAX_LEN);
			i += text.size();
			data.push_back(text);
		}
		s.clear();
		s = data[data.size() - 1];
		Editor::lastLine = s.size();
		int i = s.size();
		while (i <= 75) {
			s += " ";
			i++;
		}
		data[data.size() - 1] = s;//for last Insert
		Editor::setPage();
		myfile.close();
}//�� �������� data�� �� ���徿 ��� file�� ������ ����
/*load file�ϴ� �Լ��̴�. data ���Ϳ� 75����Ʈ ������ ���
test ������ �����Ѵ�.*/


vector<string> Editor::getBook() {
	return this->book;
}//������ tmpFile�� ������Ŀ� ���߾� ������ book�� ��ȯ�ϴ� getter.

void Editor::nextPage() {
if (Editor::nowPage+1 >= book.size()) {
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
void Editor::insert(vector<string> parameter) {
	int line;
	string msg;
	int index;
	string s;
	try {
		line = stoi(parameter[0]);
		int MAX = MAX_LINE;
		if (data.size() < MAX_LINE) {
			MAX = data.size();
		}
		if (line > MAX || line < 1) {
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
		msg = parameter[2];
		if (index < 0 || index >= MAX_LEN) {
			throw std::out_of_range("Index parameters are not appropriate.");
		}//������ 0~74����. 75 ������ ���� ���忡 ������
	}
	catch (std::invalid_argument e) {
		Editor::setState("Index must be an integer type.");
		return;
	}
	catch (std::out_of_range e) {
		Editor::setState(e.what());
		return;
	}
	if (Editor::IsBookExist) {
		if (nowPage != book.size() - 1) {
			int i = MAX_LINE * nowPage;
			for (int k = 0; k < line - 1; k++) i++;
			s = data[i];
			s.insert(index, msg);
			data[i] = s;
		}
		else {
			int lastLine = data.size() - MAX_LINE;
			if (data.size() <= MAX_LINE) {
				lastLine = 0;
			}
			for (int i = 0; i < line - 1; i++) {
				lastLine++;
			}
			s = data[lastLine];
			s.insert(index, msg);
			int refix = s.size() - 1;
			while (s[refix] == ' ') {
				s.erase(refix);
				refix--;
			}
			data[lastLine] = s;
		}//������ case�� ����� lastLine�� data���� ���� ������ data �ܾ��
		arrangePage();
		Editor::setState("Insert function Complete.");
	}
	else {
		if (line != 1) {
			Editor::setState("Book is Empty. Add 1 Line first.");
		}
		else {
			data.push_back(msg);
			arrangePage();
			Editor::setState("Insert function Complete.");
		}
	}
}

void Editor::arrangePage() {
	string s;
	string text;
	for (vector<string>::iterator it = Editor::data.begin(); it != data.end(); it++) {
		text = *it;
		if (text==data[data.size()-1]) {
			int i = text.size() - 1;
			if (i >= 0) {
				while (text[i] == ' ') {
					text.erase(i);
					i--;
					if (i <= 0) {
						text = "";
						break;
					}
				}
			}
		}
		if (strcmp(text.c_str(), "") == 0) {
			break;
		}
		else  s += text;
	}//�� �̻� �ٲ� data�� ���� �� �Ӹ��� �߰��� ���� ���ڿ��� ��ȿ���� ���� �� ����

	//�� �������� s�� ��� test.txt�� �� �������� ó��
	Editor::data.clear();
	for (int i = 0; i < s.size();) {
		string text = s.substr((int)i, (int)MAX_LEN);
		i += text.size();
		data.push_back(text);
	}
	if (data.size() > 0) {
		s = data[data.size() - 1];
		Editor::lastLine = s.size();
		int i = s.size();
		while (i < 75) {
			s += " ";
			i++;
		}
		data[data.size() - 1] = s;//for last Insert
	}
	Editor::setPage();
}//���� �Ϸ�

void Editor::del(vector<string> parameter) {
	int line;
	int index;
	int byte;
	try {
		line = stoi(parameter[0]);
		int MAX = MAX_LINE;
		if (data.size() < MAX_LINE) {
			MAX = data.size();
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
		int MAX = MAX_LEN;
		if (nowPage == book.size() - 1) {
			if (line == 20) {
				MAX = Editor::lastLine;
			}
		}

		if (index <= 0 || index > MAX) {
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
		int totalSize=0;
		if (nowPage == book.size() - 1)
		{
			if (line == 20) {
				totalSize = Editor::lastLine;
			}
			else {
				if (data.size()<=MAX_LINE) {
					for (vector<string>::iterator it = data.begin(); it != data.end(); it++) {
						totalSize += (*it).size();
					}
				}
				else {
					for (int i = 0; i < 20; i++) {
						totalSize += data[data.size() - 1 - i].size();
					}
				}
				totalSize -= (line - 1) * MAX_LEN;
			}
		}
		else totalSize = (this->data.size() - nowPage * MAX_LINE - (line - 1)) * MAX_LEN;  //���� line ��*�� ���δ� ����Ʈ
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
		if (nowPage != book.size() - 1) {
			for (vector<string>::iterator it = data.begin(); it != data.end(); it++) {
				tmp += (*it);
			}
			tmp.erase(index-1+ (nowPage)*MAX_LEN * MAX_LINE + (line - 1) * MAX_LEN, byte);//���� ���� ���� ����
			data.clear();
			if (strcmp(tmp.c_str(), "")) {
				for (int i = 0; i < tmp.size();) {
					string text = tmp.substr((int)i, (int)MAX_LEN);
					i += text.size();
					data.push_back(text);
				}
			}
		}//������ �������� �ƴ� ��,
		else {
			int row = data.size() - MAX_LINE;
			if (data.size() <= MAX_LINE) {
				row = 0;
			}
			while (row < data.size()) {
				tmp += data[row++];
			}
			tmp.erase(index - 1 + (line - 1) * MAX_LEN, byte);
			row = data.size();
			for (int i = 0; (i < MAX_LINE) && (i < row); i++) {
				data.pop_back();
			}
			if (strcmp(tmp.c_str(), "")) {
				for (int i = 0; i < tmp.size();) {
					string text = tmp.substr((int)i, (int)MAX_LEN);
					i += text.size();
					data.push_back(text);
				}
			}
		}//������ ������ �� ��.
		Editor::arrangePage();
		if (book.size() != 0) {
			while (IsPageChange()) {
				this->nowPage--;
			}//������ ���� page�� �ٲ���ٸ�
			Editor::setState("Delete function Complete.");
		}
		else {
			Editor::IsBookExist = false;
			Editor::nowPage = 0;
			Editor::setState("Delete All. If you want Insert, please insert 1 Line First.");
		}
}

void Editor::change(vector<string> parameter) {
	if (!IsBookExist) {
		Editor::setState("Book is empty.");
		return;
	}
	string msg = parameter[0];
	string change = parameter[1];
	fstream tmpStream("tmpFile.txt");
	data.clear();
	while (!tmpStream.eof()) {
		string tmp;
		getline(tmpStream,tmp);
		while (tmp.find(msg) != string::npos) {
			tmp.replace(tmp.find(msg), msg.size(), change);
		}
		data.push_back(tmp);
	}
	tmpStream.close();
	this->arrangePage();
	Editor::setState("changed Complete. " + msg + " has been changed: " + change);
}

string Editor::search(string parameter) {
	if (!IsBookExist) {
		Editor::setState("Book is empty.");
		return "";
	}
	string searching = this->book[nowPage];
	bool find = false;
	int serLine = 1;
	int serPage = 1;//�˻� �Ϸ�� ��� �˻� ���� �����ϳ��� ã�� ���� ����
	for (vector<string>::iterator it = data.begin(); it != data.end(); it++) {
		string temp = (*it);
		if (temp.find(parameter) != string::npos) {
			find = true;
			break;
		}
		serLine++;
		if (serLine > 20) {
			serPage++;
			serLine = 1;
		}//�˻� ������ 20������ ������ �������� �Ѿ.
	}
	if (find) {
		if (serPage == book.size()) {
			searching.replace(5, parameter.size(), parameter);
			setState("Search " + parameter + ". Please look at 1 Line 1 index.\n" + parameter + " was searched in " + to_string(serLine) + " Line from Last update Line");
			return searching;
		}
		searching.replace(5, parameter.size(), parameter);
		setState("Search " + parameter + ". Please look at 1 Line 1 index.\n"+parameter+" was searched in "+to_string(serPage)+" Page, " + to_string(serLine) + " Line");
		return searching;
	}
	else {
		setState("The following string could not be found within the page: " + parameter);
		return "";
	}
}


void Editor::terminal() {
	if (data.size() > 0) {
		string s = data[data.size() - 1];
		if (s[s.size() - 1] == ' ') {
			while (s[s.size() - 1] == ' ') {
				s.erase(s.size() - 1);
				if (s.size() == 0) {
					break;
				}
			}
			data[data.size() - 1] = s;
			ofstream toW("tmpFile.txt");
			for (vector<string>::iterator it = data.begin(); it != data.end(); it++) {
				toW << (*it);
			}
			toW.close();
		}
	}
	ofstream save("test.txt");
	ifstream forR("tmpFile.txt");
	while (!forR.eof()) {
		string text;
		getline(forR,text);
		save << text;
	}
	forR.close();
	save.close();
	remove("tmpFile.txt");
	setState("Program was terminated. TextFile which you wrote was saved in your file.");
}