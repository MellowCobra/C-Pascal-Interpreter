all:	main

main: main.cpp MathTokens.cpp MathTokens.h Interpreter.cpp Interpreter.h Errors.h Errors.cpp
	g++ -std=c++11 MathTokens.cpp Interpreter.cpp Errors.cpp main.cpp -o main
