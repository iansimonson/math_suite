#include "expression_tokenizer.h"

struct TokenNode * expression_tokenize(char * buffer){
	struct TokenNode * list = createToken("root",ROOTTOKEN);
    struct TokenNode * listPtr = list;

    int state = STATE_SEARCHING;
    int tmp_type;

    char tokenBuf[100];
    char * tbptr = tokenBuf;

    while(*buffer){

    	if(state == STATE_SEARCHING){
    		if(*buffer == '['){
    			state = STATE_FOUNDMATRIX;
    			tbptr = tokenBuf;
    			*tbptr++ = *buffer++;
    		} else if(isOperator(*buffer)){
    			tbptr = tokenBuf;
    			*tbptr++ = *buffer++;
    			*tbptr = '\0';

    			struct TokenNode * tmp = createToken(tokenBuf,OPERATOR);


                //Add token to the list and reset the value buffer
                listPtr->next = tmp;
                listPtr = listPtr->next;
                tbptr = tokenBuf;

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
    	} else if(state == STATE_FOUNDVALUE){
    		if(*buffer && isOperandEnd(*buffer)){
				*tbptr = '\0';

                //Initialize a VALUE token
                struct TokenNode * tmp = createToken(tokenBuf,OPERAND);


                //Add token to the list and reset the value buffer
                listPtr->next = tmp;
                listPtr = listPtr->next;
                tbptr = tokenBuf;

                //clean up and set state to searching
                tmp = NULL;
                state = STATE_SEARCHING;

    		} else {
    			*tbptr++ = *buffer++;
    			if(!(*buffer)){
    				struct TokenNode * tmp = createToken(tokenBuf,OPERAND);

	                //Add token to the list and reset the value buffer
	                listPtr->next = tmp;
	                listPtr = listPtr->next;
	                tbptr = tokenBuf;

	                //clean up and set state to searching
	                tmp = NULL;
	                state = STATE_SEARCHING;
    			}
    		}
    	} else if(state == STATE_FOUNDMATRIX){
    		if(*buffer == ']'){
    			*tbptr++ = *buffer++;
    			*tbptr = '\0';

    			struct TokenNode * tmp = createToken(tokenBuf,MATRIXELEMENT);

                //Add token to the list and reset the value buffer
                listPtr->next = tmp;
                listPtr = listPtr->next;
                tbptr = tokenBuf;

                //clean up and set state to searching
                tmp = NULL;
                state = STATE_SEARCHING;
    		} else {
    			*tbptr++ = *buffer++;
    		}
    	}
    }

    return list;
}

int isOperator(char c){
	if(c == '+' || c == '*' || c == '-' || c =='/' )
		return 1;
	else
		return 0;
}

int isOperandEnd(char c){
	if(isOperator(c) || isWS(c))
		return 1;
	else
		return 0;
}