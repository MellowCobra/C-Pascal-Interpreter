// Interprets simple addition using MathTokens
// Copyright (c) 2017 Grayson Dubois @mellowcobra

#include <string>
#include "Interpreter.h"
#include "Errors.h"

#include <iostream>

using namespace std;

Interpreter::Interpreter(string t) 
    : text(t), line(0), position(0), currentToken(_NULL) {}

Token Interpreter::getNextToken() {

    // If at the end of the text, return EOF Token
    if (this->position >= this->text.length()) {
        return Token(_EOF);
    }

    // Get the character at the current position
    char currentChar = this->text[this->position];

    // Check to see if the current character is a number or a plus sign
    if (isdigit(currentChar)) {
        Token t( (atoi(&currentChar)) );
        this->position++;
        return t;
    } else if (currentChar == '+') {
        Token t(_PLUS);
        this->position++;
        return t;
    }

    throw UnknownTokenException(this->line, this->position, currentChar);
}

void Interpreter::eat(Token t) {
    // Compare the current token type to the passed token type,
    // if they match, 'eat' the current token and assign the
    // next token to the current token
    if (this->currentToken.getType() == t.getType()) {
        this->currentToken = this->getNextToken();
    } else {
        throw UnmatchedTokenException(this->line, this->position, this->currentToken, t);
    }
}

int Interpreter::expr() {
    // expr -> INTEGER PLUS INTEGER
    this->currentToken = this->getNextToken();

    // Set the left side to current token and eat it
    Token left = this->currentToken;
    this->eat(_INTEGER);

    // We expect the next token to be a '+' token
    Token op = this->currentToken;
    this->eat(_PLUS);

    // We expect the next token to be an integer
    Token right = this->currentToken;
    this->eat(_INTEGER);

    return left.getIntValue() + right.getIntValue();
}