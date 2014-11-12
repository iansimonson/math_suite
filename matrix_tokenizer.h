#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MATRIX_TOKENIZER_H
#define MATRIX_TOKENIZER_H

#define ROOTTOKEN 0
#define LBRACKET 2
#define RBRACKET 3
#define VALUE 4
#define ROWEND 5

#define STATE_SEARCHING 0
#define STATE_FOUNDVALUE 1

struct TokenNode {
    char name[100];
    int type;
    struct TokenNode * next;
};


int isANum(char * name);
int isMatrixPart(char c);
int isValueEnd(char c);

struct TokenNode * tokenize(char * buffer);

#endif