#ifndef ABSTRACT_PARSER_H
#define ABSTRACT_PARSER_H

#include "AbstractLexer.h"

class Parser {
	
	public:
		Parser(const Lexer & input, int in_k):k(in_k){
			lexer = new ExpressionLexer(input);
			lookahead = new Token[k];
			
			for(int i = 0; i < k; ++i)
				consume();
			
		}

		virtual void consume() {
			lookahead[p] = lexer->nextToken();
			p = (++p) % k;
		}

		virtual Token lookupToken(int i){
			return lookahead[(p+i-1) % k];
		}

		virtual int lookupTokenType(int i){
			return lookupToken(i).getType();
		}

		virtual void match(int x){
			if( lookupTokenType(1) == x) consume();

			else
				throw;
		}

	private:
		Lexer * lexer;
		Token * lookahead;
		int k;
		int p = 0;
};


#endif