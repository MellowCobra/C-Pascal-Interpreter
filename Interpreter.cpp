// Interprets simple addition using MathTokens
// Copyright (c) 2017 Grayson Dubois @mellowcobra

#include <string>
#include <cctype>
#include "Interpreter.h"
#include "Errors.h"

#include <iostream>

using namespace std;

template <class T>
bool contains(T list[], T current, int max) {
    for (int i = 0; i < max; i++) {
        if (list[i].getType() == current.getType()) {
            return true;
        }
    }
    return false;
}

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
        } else if (this->currentChar == '*') {
            this->advance();
            return Token(_MUL);
        } else if (this->currentChar == '/') {
            this->advance();
            return Token(_DIV);
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
    // expr -> INTEGER ((PLUS, MINUS, MUL, DIV) INTEGER)*
    // expr -> term ((PLUS|MINUS) term)*
    // term -> INTEGER ((MUL|DIV) INTEGER)*
    this->currentToken = this->getNextToken();

    // Set the result to the value of the first token
    int result = this->term();

    // Loop for each time there is an arithmetic operator
    while (this->currentToken.getType() == _PLUS || this->currentToken.getType() == _MINUS) {
        Token t = this->currentToken;

        if (t.getType() == _PLUS) {
            this->eat(_PLUS);
            result += this->term();
        } else if (t.getType() == _MINUS) {
            this->eat(_MINUS);
            result -= this->term();
        } else {
            throw UnmatchedTokenException(this->line, this->position, this->currentToken, _PLUS);
        }
    }

    return result;
}

// Term function calculates multiplication/division terms
int Interpreter::term() {
    // term -> factor ((MUL|DIV) factor)*

    int result = this->factor();
    while (this->currentToken.getType() == _MUL || this->currentToken.getType() == _DIV) {
        Token t = this->currentToken;

        if (t.getType() == _MUL) {
            this->eat(_MUL);
            result *= this->factor();
        } else if (t.getType() == _DIV) {
            this->eat(_DIV);
            result /= this->factor();
        } else {
            throw UnmatchedTokenException(this->line, this->position, this->currentToken, _MUL);
        }
    }

    return result;
}

// Factor function consumes integers
int Interpreter::factor() {
    // factor -> INTEGER
    Token t = this->currentToken;
    this->eat(_INTEGER);
    return t.getIntValue();
}