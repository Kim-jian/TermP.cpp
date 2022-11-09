#include "Controller.h"

void Controller::run() {
	if (!model.loadFile()) {
		sc.outputLine("![Error] There is no File to perform Program.");
		return;
	}
	if (!model.makeFile()) {
		sc.outputLine("![Error] ������ �ε��ϴ� �߿� ����ġ ���� ������ �߻��߽��ϴ�.");
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
	sc.output("�Է�:");
	vector<char> e=sc.inputChar();
	int next = decide(e);
	sc.outputLine(lineSpliter);
	return next;
}