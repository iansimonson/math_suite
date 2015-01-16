#include "ExpressionLexer.h"

const std::string ExpressionLexer::tokenNames[] = {"n/a", "<EOF>", "SCALAR", "MATRIX", "PLUS", "MINUS", "MULT", "DIVIDE"};

ExpressionLexer::ExpressionLexer(std::string input):Lexer::Lexer(input){}

std::string ExpressionLexer::getTokenNames(int tokenType){
	return tokenNames[tokenType];
}

bool ExpressionLexer::isScalar(){
	return isdigit(this->c) || this->c == '-' || this->c == '.';
}

Token ExpressionLexer::nextToken() {
	while(this->c != EOF){
		switch(this->c) {
			case ' ': case '\t': case '\n': case '\r': ws(); continue;

			case '[': return matrix();

			case '+': consume(); return Token(PLUS, "+"); 
			case '-': consume(); return Token(MINUS, "-");
			case '*': consume(); return Token(MULT, "*");
			case '/': consume(); return Token(DIVIDE, "/");

			default:
				if(isScalar()) return scalar();

				throw 1;
		}
	}

	return Token(EOF_TYPE, "<EOF>");
}

Token ExpressionLexer::scalar() {
	std::stringstream ss;
	do { 
		ss << this->c;
		this->consume();	
	} while(isScalar());

	return Token(SCALAR, ss.str());
}

Token ExpressionLexer::matrix() {
	std::stringstream ss;
	do {
		ss << this->c;
		this->consume();
	} while(this->c != ']');
	
	//Add the end of the matrix
	ss << this->c;
	this->consume();

	return Token(MATRIX, ss.str());
}

void ExpressionLexer::ws() {
	while(this->c == ' ' || this->c == '\t' || this->c == '\n' || this->c == '\r')
		this->consume();
}

void ExpressionLexer::displayToken(Token t){
	std::cout << "<'" << t.getText() << "'," << tokenNames[t.getType()] << ">" << std::endl;
}