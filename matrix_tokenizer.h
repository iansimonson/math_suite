#ifndef MATRIX_TOKENIZER_H
#define MATRIX_TOKENIZER_H
#include "abstract_tokenizer.h"

int isMatrixPart(char c);
int isValueEnd(char c);

struct TokenNode * matrix_tokenize(char * buffer);

#endif