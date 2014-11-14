#include <stdio.h>
#include <stdlib.h>
#include "abstract_tokenizer.h"
#include "expression_tokenizer.h"
#include "matrix_tokenizer.h"
#include "matrix_properties.h"

int main(){
	char * expression = "[1 2:1 2]*[-1 2: -1 2]";
	struct TokenNode * tokens = expression_tokenize(expression);

	struct Matrix * m = NULL;
	struct Matrix * tmp = NULL;

	struct TokenNode * walkTokens = tokens;

	while(walkTokens){
		if(walkTokens->type == MATRIXELEMENT){
			tmp = init_matrix(walkTokens->name);
			if(m == NULL){
				m = tmp;
				tmp = NULL;
			}
			else
				m = mat_mult(m,tmp);

			print_matrix(m);
			destroy_matrix(tmp);
		}
		walkTokens = walkTokens->next;
	}

	return 0;
}
