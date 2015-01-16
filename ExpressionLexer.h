#ifndef EXPRESSION_LEXER_H
#define EXPRESSION_LEXER_H

#include <iostream>
#include <string>
#include <sstream>
#include "AbstractLexer.h"

class ExpressionLexer : public Lexer {

public:
	const static int SCALAR = 2;
	const static int MATRIX = 3;
	const static int PLUS = 4;
	const static int MINUS = 5;
	const static int MULT = 6;
	const static int DIVIDE = 7;
	const static int LPARENS = 8;
	const static int RPARENS = 9;

	const static std::string tokenNames[];

	virtual std::string getTokenNames(int tokenType);

	ExpressionLexer(std::string input);

	void displayToken(Token t);


private:
	bool isScalar();

	Token nextToken();
	Token matrix();
	Token scalar();

	void ws();

	

};

#endif