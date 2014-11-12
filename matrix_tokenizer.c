#include "matrix_tokenizer.h"


struct TokenNode * tokenize(char * buffer) {
    struct TokenNode * list = malloc(sizeof(struct TokenNode));
    struct TokenNode * listPtr = list;
    strcpy(list->name, "root");
    list->type = ROOTTOKEN;
    list->next = NULL;

    int state = STATE_SEARCHING;
    int tmp_type;
    
    char tokenBuf[100];
    char * tbptr = tokenBuf;

    /* Tokenize the entire buffer */
    while(*buffer){

        if(state == STATE_SEARCHING){

            if(tmp_type = isMatrixPart(*buffer)){

                struct TokenNode * tmp = malloc(sizeof(struct TokenNode));
                tmp->name[0] = *buffer;
                tmp->name[1] = '\0';
                tmp->type = tmp_type;
                tmp->next = NULL;

                //Add the token to the list
                listPtr->next = tmp;
                listPtr = listPtr->next;

                //for cleaning purposes
                tmp = NULL;

            } else if(isdigit(*buffer) || *buffer == '-'){
                
                tbptr = tokenBuf;
                *tbptr++ = *buffer;
                state = STATE_FOUNDVALUE;

            } else if(*buffer == '\n' || *buffer == ' '){
                
                ++buffer;
                continue;

            } else {
                fprintf(stderr, "Error: %c is not a recognized symbol.\n",*buffer);
            }

            ++buffer;


        } else if(state == STATE_FOUNDVALUE) {

            if(*buffer && isValueEnd(*buffer)) {
                //NULL TERMINATE THE STRING
                *tbptr = '\0';

                //Initialize a VALUE token
                struct TokenNode * tmp = malloc(sizeof(struct TokenNode));
                strcpy(tmp->name,tokenBuf);
                tmp->next = NULL;
                tmp->type = VALUE;

                //Add token to the list and reset the value buffer
                listPtr->next = tmp;
                listPtr = listPtr->next;
                tbptr = tokenBuf;

                //clean up and set state to searching
                tmp = NULL;
                state = STATE_SEARCHING;

            } else {

                //else keep adding chars to value buffer
                *tbptr++ = *buffer++;

            }
        }
    }

    return list;
}


void statement(struct TokenNode * input) {
    if(input == NULL)
        fprintf(stderr, "Error: empty input\n");

    else if(!strcmp(input->name,"root"))
        statement(input->next);

    else if(input && !strcmp(input->name,"[")){
        matrix(input);
    } else {
        printf("unknown.\n");
    }
}



int isANum(char * name){
    while(*name) {
        if(!isdigit(*name) && *name != '-')
            return 0;

        ++name;
    }

    return 1;
}



int isValueEnd(char c){
    if (c == ' ' || c == ':' || c == ';' || c == ']' || c == '\n' || c == '\t')
        return 1;
    else
        return 0;
}


int isMatrixPart(char c){
    if (c == '[')
        return LBRACKET;
    else if (c == ']')
        return RBRACKET;
    else if (c == ':' || c == ';')
        return ROWEND;
    else
        return 0;
}
