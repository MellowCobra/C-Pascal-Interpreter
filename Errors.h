#ifndef ERRORS_H
#define ERRORS_H
// Provides errors and exceptions that can be thrown
// in by the Interpreter
// Copyright (c) 2017 Grayson Dubois @mellowcobra

#include <exception>
#include <string>
#include "MathTokens.h"

using namespace std;

class ParsingException: public exception {
private:
    int location;
    int line;
public:
    ParsingException(const int&, const int&);

    virtual const char* what() const throw();
};

class UnknownTokenException: public ParsingException {
private: 
    char character;
public:
    UnknownTokenException(const int&, const int&, const char&);

    virtual const char* what() const throw();
};

class UnmatchedTokenException: public ParsingException {
private:
    Token currentToken;
    Token expectedToken;
public:
    UnmatchedTokenException(const int&, const int&, Token, Token);

    virtual const char* what() const throw();
};

#endif