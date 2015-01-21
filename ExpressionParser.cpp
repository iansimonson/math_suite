#include "ExpressionParser.h"

ExpressionParser::ExpressionParser(const ExpressionLexer & input, int in_k):k(in_k),lexer(input),rpn(){
	lookahead = new Token[k];
	
	for(int i = 0; i < k; ++i)
		consume();
}

ExpressionParser::ExpressionParser(const ExpressionParser & rhs):k(rhs.k),lexer(rhs.lexer),p(rhs.p),rpn(rhs.rpn) {
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
	std::swap(rpn,rhs.rpn);
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

	//expression();
	infixToRPN();
	/*while(!rpn.empty()){
		std::cout << rpn.front().getText() << " ";
		rpn.pop();
	}
	std::cout << std::endl;*/
	evaluate();

}

void ExpressionParser::infixToRPN(){
	//lexer.rewind();
	std::stack<Token> ops;
	Token t;
	int tmpType;

	while((t = lookupToken(1)).getType() != Lexer::EOF_TYPE){
		consume();
		tmpType = t.getType();
		if(tmpType == ExpressionLexer::SCALAR || tmpType == ExpressionLexer::MATRIX){
			rpn.push(t);
		} else if(isOperator(tmpType)){
			while(!ops.empty() && isOperator(ops.top().getType()) && tmpType/6 <= ops.top().getType()/6){
				rpn.push(ops.top());
				ops.pop();
			}
			ops.push(t);
		} else if(tmpType == ExpressionLexer::LPARENS){
			ops.push(t);
		} else if(tmpType == ExpressionLexer::RPARENS){
			while(ops.top().getType() != ExpressionLexer::LPARENS){
				rpn.push(ops.top());
				ops.pop();
				if(ops.empty())
					throw 10;
			}
			ops.pop();
		} else {
			throw 1;
		}
	}

	while(!ops.empty()){
		if(ops.top().getType() == ExpressionLexer::LPARENS){
			throw 10;
		} else {
			rpn.push(ops.top());
			ops.pop();	
		}
		
	}
}

void ExpressionParser::evaluate() {

	Token t1,t2;
	bool matFlag = false;

	Matrix resultM;
	double resultS;

	std::stack<Token> values;
	
	while(!rpn.empty()){
		switch(rpn.front().getType()){
			case ExpressionLexer::MATRIX: 
				matFlag = true;
			case ExpressionLexer::SCALAR:
				values.push(rpn.front());
				
				break;
			case ExpressionLexer::PLUS: 
				t1 = values.top();
				values.pop();
				t2 = values.top();
				values.pop();

				if(matFlag){
					if(t1.getType() == ExpressionLexer::MATRIX && t2.getType() == ExpressionLexer::MATRIX){
						resultM = MatProps::add(Matrix(t1.getText()),Matrix(t2.getText()));
						values.push(Token(ExpressionLexer::MATRIX,resultM.to_str()));
					} else if(t1.getType() == ExpressionLexer::SCALAR && t2.getType() == ExpressionLexer::SCALAR){
						resultS = std::stod(t1.getText()) + std::stod(t2.getText());
						values.push(Token(ExpressionLexer::SCALAR,std::to_string(resultS)));
					} else {
						throw 2;
					}
				} else {
					resultS = std::stod(t1.getText()) + std::stod(t2.getText());
					values.push(Token(ExpressionLexer::SCALAR,std::to_string(resultS)));
				}

				break;

			case ExpressionLexer::MINUS:

				t1 = values.top();
				values.pop();
				t2 = values.top();
				values.pop();

				if(matFlag){
					if(t1.getType() == ExpressionLexer::MATRIX && t2.getType() == ExpressionLexer::MATRIX){
						resultM = MatProps::add(Matrix(t1.getText()),MatProps::multiply(-1,Matrix(t2.getText())));
						values.push(Token(ExpressionLexer::MATRIX,resultM.to_str()));
					} else if(t1.getType() == ExpressionLexer::SCALAR && t2.getType() == ExpressionLexer::SCALAR){
						resultS = std::stod(t1.getText()) - std::stod(t2.getText());
						values.push(Token(ExpressionLexer::SCALAR,std::to_string(resultS)));
					} else {
						throw 2;
					}
				} else {
					resultS = std::stod(t1.getText()) - std::stod(t2.getText());
					values.push(Token(ExpressionLexer::SCALAR,std::to_string(resultS)));
				}

				break;

			case ExpressionLexer::MULT:
				t1 = values.top();
				values.pop();
				t2 = values.top();
				values.pop();

				if(t1.getType() == ExpressionLexer::MATRIX && t2.getType() == ExpressionLexer::MATRIX){
					resultM = MatProps::multiply(Matrix(t1.getText()),Matrix(t2.getText()));
					values.push(Token(ExpressionLexer::MATRIX,resultM.to_str()));
				} else if(t1.getType() == ExpressionLexer::MATRIX && t2.getType() == ExpressionLexer::SCALAR){
					resultM = MatProps::multiply(Matrix(t1.getText()),std::stod(t2.getText()));
					values.push(Token(ExpressionLexer::MATRIX,resultM.to_str()));
				} else if(t1.getType() == ExpressionLexer::SCALAR && t2.getType() == ExpressionLexer::MATRIX){
					resultM = MatProps::multiply(std::stod(t1.getText()),Matrix(t2.getText()));
					values.push(Token(ExpressionLexer::MATRIX,resultM.to_str()));
				} else {
					resultS = std::stod(t1.getText()) * std::stod(t2.getText());
					values.push(Token(ExpressionLexer::SCALAR,std::to_string(resultS)));
				}

				break;

			case ExpressionLexer::DIVIDE:
				t1 = values.top();
				values.pop();
				t2 = values.top();
				values.pop();
				
				if(t1.getType() == ExpressionLexer::MATRIX && t2.getType() == ExpressionLexer::SCALAR){
					resultM = MatProps::divide(Matrix(t1.getText()),std::stod(t2.getText()));
					values.push(Token(ExpressionLexer::MATRIX,resultM.to_str()));
				} else if(t1.getType() == ExpressionLexer::SCALAR && t2.getType() == ExpressionLexer::MATRIX){
					resultM = MatProps::divide(std::stod(t1.getText()),Matrix(t2.getText()));
					values.push(Token(ExpressionLexer::MATRIX,resultM.to_str()));
				} else if(t1.getType() == ExpressionLexer::SCALAR && t2.getType() == ExpressionLexer::SCALAR){
					resultS = std::stod(t1.getText()) / std::stod(t2.getText());
					values.push(Token(ExpressionLexer::SCALAR,std::to_string(resultS)));
				} else {
					throw 2;
				}

				break;
				
		}
		rpn.pop();
	}

	if(matFlag){
		t1 = values.top();
		Matrix(t1.getText()).display();
	} else {
		std::cout << std::stod(values.top().getText()) << std::endl;
	}
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