//Controller class
#include "Controller.h"

#define MAX_LINE 20


#pragma warning(push)
#pragma warning(disable:6031)
void Controller::run() {
	if (!model.loadFile()) {
		sc.outputLine("![Error] There is no File to perform Program.");
		getchar();
		return;
	}
	int k = show();
	while (k) {
		k = show();
	}
	sc.outputLine("Program was terminated. Press Any Key to close this Window.");
	getchar();
}
#pragma warning(pop)

int Controller::decide(string e) {
	char sentry = e[0];
	switch (sentry) {
	case 't':
	{
		model.terminal();
		return 0;
	}
	case 'n': {
		model.nextPage();
		return 1;
	}
	case 'p': {
		model.prePage();
		return 1;
	}
	case 'i': {
		if (e.size() < 8 || e[e.size() - 1] != ')' || e[1] != '(') {
			model.setState("Format Error. Insert function's format is i(int line, int index, string message).");
			return 1;
		}
		int pos;
		int current = 2;
		e.erase(e.size() - 1);
		vector<string> parameter;
		while ((pos = e.find(",", current)) != std::string::npos) {
			int len = pos - current;
			string result = e.substr(current, len);
			parameter.push_back(result);
			current = pos + 1;
			if (parameter.size() >= 2) {
				parameter.push_back(e.substr(current, e.size() - 1));
			}//이미 2개 찾았으면 그 뒤에 ,는 전부 입력할 string
		}
		if (current < 6) {
			model.setState("Format Error. Insert function's format is i(int line, int index, string message).");
			return 1;
		}
		string result = e.substr(current);
		parameter.push_back(result);
		model.insert(parameter);
		return 1;
	}
	case 'd':
	{
		if (e.size() < 8 || e[e.size() - 1] != ')' || e[1] != '(') {
			model.setState("Format Error. Delete function's format is d(int line, int index, int byte).");
			return 1;
		}
		vector<string> parameter;
		int pos;
		int current = 2;
		e.erase(e.size() - 1);
		while ((pos = e.find(",", current)) != std::string::npos) {
			int len = pos - current;
			string result = e.substr(current, len);
			parameter.push_back(result);
			current = pos + 1;
		}
		if (current < 6) {
			model.setState("Format Error. Delete function's format is d(int line, int index, int byte).");
			return 1;
		}
		string result = e.substr(current);
		parameter.push_back(result);
		model.del(parameter);
		return 1;
	}
	case 'c':
	{
		if (e.size() < 6 || e[e.size() - 1] != ')' || e[1] != '(') {
			model.setState("Format Error. Change function's format is c(string msg, string changeMsg).");
			return 1;
		}
		vector<string> parameter;
		int pos;
		int current = 2;
		e.erase(e.size() - 1);
		while ((pos = e.find(",", current)) != std::string::npos) {
			int len = pos - current;
			string result = e.substr(current, len);
			parameter.push_back(result);
			current = pos + 1;
		}
		if (current < 4) {
			model.setState("Format Error. Change function's format is i(int line, int index, string message).");
			return 1;
		}
		string result = e.substr(current);
		parameter.push_back(result);
		model.change(parameter);
		return 1;
	}
	case 's': {
		if (e.size() < 4 || e[e.size() - 1] != ')' || e[1] != '(') {
			model.setState("Format Error. Search function's format is s(string message).");
			return 1;
		}
		e.erase(e.size() - 1);
		e.erase(0, 2);
		string searched = model.search(e);
		if (searched != "") {
			sc.outputLine(lineSpliter);
			sc.outputLine(searched);
		}
		return 1;
	}
	default: {
		model.setState("Text Edit Program can service\ni: Insert\nd: Delete\ns: Search\nn: Next Page\np: Previous Page\nt: Terminate.");
	}
	}
}


int Controller::show() {
	Controller::page = model.getPage();
	if (model.IsBookExist) {
		Controller::book = model.getBook();
		sc.outputLine(book[page]);
	}
	sc.outputLine(lineSpliter);
	sc.outputLine(menu);
	sc.outputLine(lineSpliter);
	sc.outputLine(model.getState());
	sc.outputLine(lineSpliter);
	sc.output("입력:");
	string e = sc.inputString();
	int next = decide(e);
	sc.outputLine(lineSpliter);
	return next;
}