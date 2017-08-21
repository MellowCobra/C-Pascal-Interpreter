// Interprets simple addition using MathTokens
// Copyright (c) 2017 Grayson Dubois @mellowcobra

#include <string>
#include <cctype>
#include "Interpreter.h"
#include "Errors.h"

#include <iostream>

using namespace std;


#define NULLCHAR '\0'

Interpreter::Interpreter(string t) 
    : text(t), line(0), position(0), currentToken(_NULL) {
        this->currentChar = this->text[this->position];
}

// Advance the position and set the current character
void Interpreter::advance() {

    this->position++;

    // If at the end of the string, set current character
    // to the terminating character
    if (this->position >= this->text.length()) {
        this->currentChar = NULLCHAR;
    } else {
        this->currentChar = this->text[this->position];
    }
}

void Interpreter::skipWhitespace() {
    while (this->currentChar != NULLCHAR && isspace(this->currentChar)) {
        this->advance();
    }
}

// Return a multidigit integer consumed from input
int Interpreter::integer() {
    string result = "";

    // If not at the end of string and current char is a digit,
    // add the current char to the result string
    while (this->currentChar != NULLCHAR && isdigit(this->currentChar)) {
        result += this->currentChar;
        this->advance();
    }

    // Convert result string to int and return
    return stoi(result);
}

/****** Lexical Analyzer ******/
// Breaks input into tokens
Token Interpreter::getNextToken() {

    while (this->currentChar != NULLCHAR) {
        if (isspace(this->currentChar)) {
            this->skipWhitespace();
            continue;
        } else if (isdigit(this->currentChar)) {
            return Token(this->integer());
        } else if (this->currentChar == '+') {
            this->advance();
            return Token(_PLUS);
        } else if (this->currentChar == '-') {
            this->advance();
            return Token(_MINUS);
        } else {
            throw UnknownTokenException(this->line, this->position, this->currentChar);
        }
    }

    return Token(_EOF);
}

void Interpreter::eat(Type t) {
    // Compare the current token type to the passed token type,
    // if they match, 'eat' the current token and assign the
    // next token to the current token
    if (this->currentToken.getType() == t) {
        this->currentToken = this->getNextToken();
    } else {
        throw UnmatchedTokenException(this->line, this->position, this->currentToken, t);
    }
}

// Parser / Interpreter
int Interpreter::expr() {
    // expr -> INTEGER PLUS INTEGER
    // expr -> INTEGER MINUS INTEGER
    this->currentToken = this->getNextToken();

    // Set the left side to current token and eat it
    Token left = this->currentToken;
    this->eat(_INTEGER);

    // We expect the next token to be a '+' token
    Token op = this->currentToken;
    if (op.getType() == _PLUS) {
        this->eat(_PLUS);
    } else if (op.getType() == _MINUS) {
        this->eat(_MINUS);
    } else {
        throw UnmatchedTokenException(this->line, this->position, this->currentToken, _PLUS);
    }

    // We expect the next token to be an integer
    Token right = this->currentToken;
    this->eat(_INTEGER);

    int result = 0;
    if (op.getType() == _PLUS) {
        result = left.getIntValue() + right.getIntValue();
    } else if (op.getType() == _MINUS) {
        result = left.getIntValue() - right.getIntValue();
    }
    return result;
}