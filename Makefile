CFLAGS= -std=c++11

mmult: matrix_multiplier.o matrix.o
	g++ -o mmult matrix_multiplier.o matrix.o $(CFLAGS)

matrix_multiplier.o: matrix_multiplier.cpp matrix.h
	g++ -c matrix_multiplier.cpp $(CFLAGS)

matrix.o: matrix.cpp matrix.h
	g++ -c matrix.cpp $(CFLAGS)

parseTest: testParser.o ExpressionParser.o ExpressionLexer.o Token.o
	g++ -g -o parseTest ExpressionParser.o testParser.o ExpressionLexer.o Token.o $(CFLAGS)

testParser.o: testParser.cpp
	g++ -g -c testParser.cpp $(CFLAGS)

ExpressionParser.o: ExpressionLexer.h
	g++ -g -c ExpressionParser.cpp $(CFLAGS)

lexTest: testLexer.o ExpressionLexer.o Token.o
	g++ -g -o lexTest testLexer.o ExpressionLexer.o Token.o $(CFLAGS)

testLexer.o: testLexer.cpp AbstractLexer.h Token.h
	g++ -g -c testLexer.cpp $(CFLAGS)

ExpressionLexer.o: ExpressionLexer.h ExpressionLexer.cpp AbstractLexer.h Token.h
	g++ -g -c ExpressionLexer.cpp $(CFLAGS)

Token.o: Token.cpp Token.h
	g++ -g -c Token.cpp $(CFLAGS)

clean:
	rm *.o
	rm lexTest
	rm parseTest
