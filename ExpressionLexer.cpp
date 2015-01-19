#include "ExpressionLexer.h"

const std::string ExpressionLexer::tokenNames[] = {"n/a", "<EOF>", "SCALAR", "MATRIX", "PLUS", "MINUS", "MULT", "DIVIDE"};

ExpressionLexer::ExpressionLexer(std::string input):Lexer::Lexer(input){}

std::string ExpressionLexer::getTokenNames(int tokenType){
	return tokenNames[tokenType];
}

bool ExpressionLexer::isScalar(char t){
	return isdigit(t) || t == '-' || t == '.';
}

bool ExpressionLexer::isSubtraction(){
	//If there is a minus sign floating, assume subtraction
	if(isWS(this->input[p+1]))
		return true;


	//Else, check to see if there was an operator or not beforehand
	int tmp = (this->p) - 1;
	while(tmp >= 0 && isWS(this->input[tmp]))
		--tmp;

	if(tmp >= 0 && this->input[tmp] == '+' || this->input[tmp] == '-' || this->input[tmp] == '*' || this->input[tmp] == '/' || tmp < 0)
		return false;
	else
		return true;
}

bool ExpressionLexer::isWS(char t){
	return t == ' ' || t == '\t' || t == '\n' || t == '\r';
}

Token ExpressionLexer::nextToken() {

	while(this->c != EOF){
		switch(this->c) {
			case ' ': case '\t': case '\n': case '\r': ws(); continue;

			case '[': return matrix();

			case '(': consume(); return Token(LPARENS, "(");
			case ')': consume(); return Token(RPARENS, ")");

			case '+': consume(); return Token(PLUS, "+"); 
			case '-': if(isSubtraction()) {consume(); return Token(MINUS, "-");}
					else {return scalar();}
			case '*': consume(); return Token(MULT, "*");
			case '/': consume(); return Token(DIVIDE, "/");

			default:
				if(isScalar(this->c)) return scalar();

				throw 1;
		}
	}

	return Token(EOF_TYPE, "<EOF>");
}


//Extracts the current scalar element
Token ExpressionLexer::scalar() {
	std::stringstream ss;
	do { 
		ss << this->c;
		this->consume();	
	} while(isScalar(this->c));

	return Token(SCALAR, ss.str());
}


//Extracts the current matrix element
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

//Consumes all whitespace until something useful shows up
void ExpressionLexer::ws() {
	while(isWS(this->c))
		this->consume();
}

//Allows different Lexers to display the token names
//Tokens normally display their types just as numbers
void ExpressionLexer::displayToken(Token t){
	std::cout << "<'" << t.getText() << "'," << tokenNames[t.getType()] << ">" << std::endl;
}