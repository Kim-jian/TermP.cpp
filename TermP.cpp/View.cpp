//View Class
#include "View.h"

void View::output(std::string msg) {
	std::cout << msg;
}
void View::outputLine(std::string msg) {
	std::cout << msg << std::endl;
}
std::string View::inputString() {
	std::string input;
	std::getline(std::cin, input);
	return input;
}