#ifndef INTERPRETER_H
#define INTERPRETER_H
// Interprets mathematical formulae using MathTokens library
// Copyright (c) 2017 Grayson Dubois @mellowcobra

#include "MathTokens.h"

class Interpreter {
private:
    int line;
    int position;
    string text;
    char currentChar;
    Token currentToken;

public:
    Interpreter(string);

    void advance();
    void skipWhitespace();
    int integer();

    Token getNextToken();
    void eat(Type);
    int expr();
    int term();
    int factor();
};

#endif