#ifndef EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_H

#include "ExpressionLexer.h"

class ExpressionParser {

public:
	ExpressionParser(const ExpressionLexer & input, int in_k);
	
	ExpressionParser(const ExpressionParser & rhs);
	~ExpressionParser();
	ExpressionParser & operator=(const ExpressionParser & rhs);
	void swap(ExpressionParser & rhs);

	void consume();

	Token lookupToken(int i) const;

	int lookupTokenType(int i) const;

	void match(int x);

	void parse();

private:
	ExpressionLexer lexer;
	Token * lookahead;
	int k;
	int p = 0;

	bool isOperator(int type);

	void expression();
	void op();
	void element();
};

#endif