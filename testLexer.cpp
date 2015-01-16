#include <iostream>
#include "ExpressionLexer.h"

int main() {
	std::cout << "Enter expression: ";
	std::string input;
	getline(std::cin,input,'\n');
	Lexer* lexer = new ExpressionLexer(input);
	Token t;
	t = lexer->nextToken();

	while(t.getType() != Lexer::EOF_TYPE){
		lexer->displayToken(t);
		t = lexer->nextToken();	
		
	}
}