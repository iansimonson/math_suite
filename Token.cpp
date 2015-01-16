#include "Token.h"

Token::Token():mType(0),mText("") {}
Token::Token(int type, std::string text):mType(type),mText(text) {}

void Token::display(){
	std::cout << "<'" << mText << "'," << mType << ">";
}

int Token::getType(){
	return mType;
}
std::string Token::getText(){
	return mText;
}
