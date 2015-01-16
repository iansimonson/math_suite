#ifndef ABSTRACT_LEXER_H
#define ABSTRACT_LEXER_H

#include <iostream>
#include "Token.h"

class Lexer {

public:

	const static int EOF_TYPE = 1;

	Lexer(std::string input){
		this->input = input;
		c = this->input[0];
	}

	virtual void consume(){
		if(++p >= input.length())
			c = EOF;
		else
			c = input[p];
	}

	virtual void match(char x){
		if(c==x) 
			consume();
		else
			throw;
	}
	virtual Token nextToken() = 0;
	virtual std::string getTokenNames(int tokenType) = 0;
	virtual void displayToken(Token t) = 0;

protected:

	std::string input;
	int p = 0;
	char c;
};

#endif