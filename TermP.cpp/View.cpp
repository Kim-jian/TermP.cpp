#include "View.h"

void View::output(std::string msg) {
	std::cout << msg;
}
void View::outputLine(std::string msg) {
	std::cout << msg << std::endl;
}
std::vector<char> View::inputChar() {
	std::string input;
	std::cin >> input;
	std::vector<char> result;
	std::stringstream ss(input);
	ss.str(input);
	while (!ss.eof()) {
		char tmp;
		ss >> tmp;
		result.push_back(tmp);
	}
	return result;
}