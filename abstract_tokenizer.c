#include "abstract_tokenizer.h"

int isANum(char * name){
    while(*name) {
        if(!isdigit(*name) && *name != '-')
            return 0;

        ++name;
    }
    
    return 1;
}

int isWS(char c){
	if(c == ' ' || c == '\n' || c == '\t' || c == '\r')
		return 1;
	else
		return 0;
}

struct TokenNode * createToken(char * name, int type){
	struct TokenNode * tmp = malloc(sizeof(struct TokenNode));
	strcpy(tmp->name,name);
	tmp->type = type;
    tmp->next = NULL;

    return tmp;
}