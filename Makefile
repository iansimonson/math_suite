CFLAGS= -std=c++11
OBJECTS= ExpressionParser.o ExpressionLexer.o Token.o matrix.o
all: matrix.o Token.o ExpressionLexer.o ExpressionParser.o parseTest

parseTest: testParser.cpp ExpressionParser.o ExpressionLexer.o Token.o matrix.o
	g++ -o parseTest testParser.cpp ExpressionParser.o ExpressionLexer.o Token.o matrix.o $(CFLAGS)

ExpressionParser.o: ExpressionParser.cpp ExpressionParser.h ExpressionLexer.h matrix.h Token.h
	g++ -c ExpressionParser.cpp $(CFLAGS)

ExpressionLexer.o: ExpressionLexer.cpp ExpressionLexer.h AbstractLexer.h Token.h
	g++ -c ExpressionLexer.cpp $(CFLAGS)

Token.o: Token.cpp Token.h
	g++ -c Token.cpp $(CFLAGS)

matrix.o: matrix.cpp matrix.h
	g++ -c matrix.cpp $(CFLAGS)

clean:
	rm matrix.o
	rm Token.o
	rm ExpressionLexer.o
	rm ExpressionParser.o
	rm parseTest
