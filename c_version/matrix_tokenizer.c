#include "matrix_tokenizer.h"


struct TokenNode * matrix_tokenize(char * buffer) {
    struct TokenNode * list = createToken("root",ROOTTOKEN);
    struct TokenNode * listPtr = list;

    int state = STATE_SEARCHING;
    int tmp_type;
    
    char tokenBuf[100];
    char * tbptr = tokenBuf;

    /* Tokenize the entire buffer */
    while(*buffer){

        if(state == STATE_SEARCHING){

            if(tmp_type = isMatrixPart(*buffer)){
                
                tbptr = tokenBuf;
                *tbptr++ = *buffer;
                *tbptr = '\0';

                struct TokenNode *tmp = createToken(tokenBuf,tmp_type);
                
                //Add the token to the list
                listPtr->next = tmp;
                listPtr = listPtr->next;

                //for cleaning purposes
                tmp = NULL;

            } else if(isdigit(*buffer) || *buffer == '-'){
                
                tbptr = tokenBuf;
                *tbptr++ = *buffer;
                state = STATE_FOUNDVALUE;

            } else if(isWS(*buffer)){
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
                struct TokenNode * tmp = createToken(tokenBuf,VALUE);

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




/* Helper methods for the tokenizing process */



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
