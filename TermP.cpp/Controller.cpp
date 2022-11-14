//Controller class
#include "Controller.h"

void Controller::run() {
	if (!model.loadFile()) {
		sc.outputLine("![Error] There is no File to perform Program.");
		return;
	}
	if (!model.makeFile()) {
		sc.outputLine("![Error] 파일을 로드하는 중에 예상치 못한 오류가 발생했습니다.");
		return;
	}
	book = model.getBook();
	int k = show();
	while (k) {
		k = show();
	}
	return;
}

int Controller::decide(string e) {
	char sentry = e[0];
	switch (sentry) {
	case 't':
		return 0;
	case 'n':
		model.nextPage();
		return 1;
	case 'p':
		model.prePage();
		return 1;
	case 'i':
		if (e.size()<8||e[e.size()-1]!=')') {
			model.setState("Format Error. Insert function's format is i(int line, int index, string message).");
			return 1;
		}
		int pos;
		int current = 2;
		e.erase(e.size()-1);
		vector<string> parameter;
		while ((pos = e.find(",", current)) != std::string::npos) {
				int len = pos - current;
				string result = e.substr(current, len);
				parameter.push_back(result);
				current = pos + 1;
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
}

Controller::Controller() {
	
}

int Controller::show() {
	sc.output(Controller::model.showBook());
	sc.outputLine(lineSpliter);
	sc.outputLine(menu);
	sc.outputLine(lineSpliter);
	sc.outputLine(model.getState());
	sc.outputLine(lineSpliter);
	sc.output("입력:");
	string e=sc.inputString();
	int next = decide(e);
	sc.outputLine(lineSpliter);
	return next;
}