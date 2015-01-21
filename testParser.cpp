#include <iostream>
#include "ExpressionParser.h"

int main() {
	std::cout << "Enter expression: ";
	std::string input;
	getline(std::cin,input,'\n');
	ExpressionLexer lexer(input);
	ExpressionParser parser(lexer,3);
	
	parser.parse(); 
}