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

int Controller::decide(std::vector<char> e) {
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
	default:
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
	vector<char> e=sc.inputChar();
	int next = decide(e);
	sc.outputLine(lineSpliter);
	return next;
}