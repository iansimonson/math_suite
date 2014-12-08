#include "expression_parser.h"
#include "matrix_properties.h"

struct TokenNode * nextToken(struct ExpressionParser * parser){
	return parser->expression;
}

struct TokenNode * lookAheadToken(struct ExpressionParser * parser){
	return (parser->expression == NULL) ? NULL : parser->expression->next;
}

struct ExpressionParser * init_parser(char * input){
	struct ExpressionParser * parser = malloc(sizeof(struct ExpressionParser));
	parser->expression = expression_tokenize(input);

	return parser;
}

void destroy_parser(struct ExpressionParser * parser){
	if(parser != NULL){
		if(parser->expression != NULL){
			destroyTokens(parser->expression);
		}
		free(parser);
	}
}

char * evaluate(struct ExpressionParser * parser){
	struct Matrix * curResult = NULL;
	struct TokenNode * LA = NULL;
	struct TokenNode * curNode = NULL;
	while(curNode = nextToken(parser)){
		LA = lookAheadToken(parser);
		if(curResult == NULL && curNode->type != MATRIXELEMENT){
			return NULL;
		} else if(curResult == NULL && curNode->type == MATRIXELEMENT){
			curResult = init_matrix(curNode->name);
		}

		
	}

}