#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
#include <string>

class Token {
public:
	Token();
	Token(int type, std::string text);
	
	int getType();
	std::string getText();
	void display();

private:
	int mType;
	std::string mText;
};

#endif