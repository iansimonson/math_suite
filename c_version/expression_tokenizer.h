#ifndef EXPR_TOKENIZER_H
#define EXPR_TOKENIZER_H
#include "abstract_tokenizer.h"

struct TokenNode * expression_tokenize(char * buffer);

int isOperand(char c);
int isOperandEnd(char c);
int isOperator(char c);

#endif