CFLAGS= -std=c++11

mmult: matrix_multiplier.o matrix.o
	g++ -o mmult matrix_multiplier.o matrix.o $(CFLAGS)

matrix_multiplier.o: matrix_multiplier.cpp matrix.h
	g++ -c matrix_multiplier.cpp $(CFLAGS)

matrix.o: matrix.cpp matrix.h
	g++ -c matrix.cpp $(CFLAGS)

lexTest: testLexer.o ExpressionLexer.o Token.o
	g++ -g -o lexTest testLexer.o ExpressionLexer.o Token.o $(CFLAGS)

testLexer.o: testLexer.cpp AbstractLexer.h Token.h
	g++ -g -c testLexer.cpp $(CFLAGS)

ExpressionLexer.o: ExpressionLexer.h ExpressionLexer.cpp AbstractLexer.h Token.h
	g++ -g -c ExpressionLexer.cpp $(CFLAGS)

Token.o: Token.cpp Token.h
	g++ -g -c Token.cpp $(CFLAGS)

clean:
	rm Token.o
	rm ExpressionLexer.o
	rm testLexer.o
	rm matrix.o
	rm matrix_multiplier.o
