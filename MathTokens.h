#ifndef MATH_TOKENS_H
#define MATH_TOKENS_H

// Interprets tokens for math symbols
// Copyright (c) 2017 Grayson Dubois @mellowcobra

#include <string>
using std::string;

// Token types
// End of file token used to indicate no more input for lexical analysis
//#define INTEGER = "INTEGER"
//#define PLUS = "PLUS"
//#define EOF = "EOF"

enum Type {_INTEGER, _PLUS, _EOF};

class Token {

    // Properties
    Type type;              // Describes the token type
    void* value;            // Describes the value of the token

public:
    // Constructors
    Token();
    Token(Type, void*);
    Token(int);
    Token(Type);

    // Accessors
    Type getType();
    void* getValue();
    int getIntValue();

    // Mutators
    void setToken(Type, void*);

    // Convenience Methods
    string stringRepresentation();
};

#endif