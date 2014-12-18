#ifndef EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_H
#include "expression_tokenizer.h"

struct ExpressionParser {
	struct TokenNode * expression;
};

struct TokenNode * nextToken(struct ExpressionParser * parser);
struct TokenNode * lookAheadToken(struct ExpressionParser * parser);

struct ExpressionParser * init_parser(char * input);
void destroy_parser(struct ExpressionParser * parser);

char * evaluate(struct ExpressionParser * parser);

#endif