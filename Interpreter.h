#ifndef INTERPRETER_H
#define INTERPRETER_H
// Interprets mathematical formulae using MathTokens library
// Copyright (c) 2017 Grayson Dubois @mellowcobra

#include "MathTokens.h"

class Interpreter {
private:
    int position;
    string text;
    Token currentToken;

public:
    Interpreter(string);

    Token getNextToken();
};

#endif