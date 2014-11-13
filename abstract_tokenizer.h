#ifndef ABSTRACT_TOKENIZER_H
#define ABSTRACT_TOKENIZER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROOTTOKEN 0
#define SUBEXPRESSION 1
#define OPERATOR 2
#define OPERAND 3
#define LBRACKET 4
#define RBRACKET 5
#define VALUE 6
#define ROWEND 7
#define MATRIXELEMENT 8

#define STATE_SEARCHING 0
#define STATE_FOUNDVALUE 1
#define STATE_FOUNDMATRIX 2

struct TokenNode {
    char name[100];
    int type;
    struct TokenNode * next;
};

struct TokenNode * createToken(char * name, int type);

int isANum(char * name);
int isWS(char c);

#endif