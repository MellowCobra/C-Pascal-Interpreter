// Interprets simple addition using MathTokens
// Copyright (c) 2017 Grayson Dubois @mellowcobra

#include "Interpreter.h"
#include <string>

using std::string;
using std::to_string;

Interpreter::Interpreter(string t) {
    this->text = t;
}

Token Interpreter::getNextToken() {

    // If at the end of the text, return EOF Token
    if (this->position > this->text.length()) {
        return Token(_EOF);
    }

    // Get the character at the current position
    char currentChar = this->text[this->position];

    // Check to see if the current character is a number or a plus sign
    if (isdigit(currentChar)) {
        Token t( (int(currentChar)) );
        this->position++;
        return t;
    } else if (currentChar == '+') {
        Token t(_PLUS);
        this->position++;
        return t;
    }

    throw ("Unrecognized token " + to_string(currentChar) + " at position " + to_string(this->position));
}