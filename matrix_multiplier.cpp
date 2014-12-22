#include <iostream>
#include "matrix.h"
using namespace MatProps;

void welcome(void);
void parseInput(const std::string & input);

int main() {

	welcome();

	std::string input = "";

	bool quit = false;

	do {
		std::cout << "=$> ";
		getline(std::cin, input, '\n');

		if(input == "quit" || input == "q" || input == "exit"){
			quit = true;
			continue;
		} else {
			parseInput(input);
		}

	} while(!quit);

	std::cout << std::endl;

	return 0;

}

void welcome(void){
	std::cout << std::endl;
	std::cout << "MATRIX MATH CALCULATOR" << std::endl;
	std::cout << "----------------------" << std::endl;
	std::cout << std::endl;
}

void parseInput(const std::string & input){
	if(input[0] == '['){
		Matrix tmp(input.substr(0,input.find(']')+1));
		display(tmp);
	}
}