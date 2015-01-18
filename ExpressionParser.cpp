#include "ExpressionParser.h"

ExpressionParser::ExpressionParser(const ExpressionLexer & input, int in_k):k(in_k),lexer(input){
	lookahead = new Token[k];
	
	for(int i = 0; i < k; ++i)
		consume();
}

ExpressionParser::ExpressionParser(const ExpressionParser & rhs):k(rhs.k),lexer(rhs.lexer),p(rhs.p) {
	lookahead = new Token[k];
	for(int i = 0; i < k; ++i)
		lookahead[i] = rhs.lookahead[i];
}


ExpressionParser::~ExpressionParser(){
	delete [] lookahead;
}

ExpressionParser & ExpressionParser::operator=(const ExpressionParser & rhs){
	if(this != &rhs){
		ExpressionParser tmp(rhs);
		swap(tmp);
	}
	return *this;
}


void ExpressionParser::swap(ExpressionParser & rhs) {
	std::swap(k, rhs.k);
	std::swap(lexer,rhs.lexer);
	std::swap(p, rhs.p);
	std::swap(lookahead, rhs.lookahead);
}

void ExpressionParser::consume() {
	lookahead[p] = lexer.nextToken();
	p = (++p) % k;
}

Token ExpressionParser::lookupToken(int i) const{
	return lookahead[(p+i-1) % k];
}

int ExpressionParser::lookupTokenType(int i) const{
	return lookupToken(i).getType();
}

void ExpressionParser::match(int x){
	if( lookupTokenType(1) == x) consume();

	else
		throw;
}


void ExpressionParser::parse(){
	/*Token t;
	t = lookupToken(1);

	while(t.getType() != Lexer::EOF_TYPE){
		lexer.displayToken(t);
		consume();
		t = lookupToken(1);	
	}*/

	expression();
}

void ExpressionParser::expression(){
	element();
	if(isOperator(lookupTokenType(1))) {
		op();
		expression();
	}
}

void ExpressionParser::op(){
	std::cout << "OPERATOR: ";
	lexer.displayToken(lookupToken(1));
	switch(lookupTokenType(1)){
		case ExpressionLexer::PLUS:
			match(ExpressionLexer::PLUS);
			break;
		case ExpressionLexer::MINUS:
			match(ExpressionLexer::MINUS);
			break;
		case ExpressionLexer::MULT:
			match(ExpressionLexer::MULT);
			break;
		case ExpressionLexer::DIVIDE:
			match(ExpressionLexer::DIVIDE);
			break;
		default:
			throw 1;
	}
}

void ExpressionParser::element(){
	std::cout << "ELEMENT: ";
	lexer.displayToken(lookupToken(1));
	if(lookupTokenType(1) == ExpressionLexer::SCALAR){
		match(ExpressionLexer::SCALAR);
	} else if(lookupTokenType(1) == ExpressionLexer::MATRIX){
		match(ExpressionLexer::MATRIX);
	} else {
		throw 1;
	}
}

bool ExpressionParser::isOperator(int type){
	return type >= ExpressionLexer::PLUS && type <= ExpressionLexer::DIVIDE;
}