// Interprets tokens for math symbols
// Copyright (c) 2017 Grayson Dubois @mellowcobra

#include "MathTokens.h"

Token::Token() {
    this->setToken(_EOF, (void*)(new string("eof")));
}

Token::Token(Type t, void* v) {
    this->setToken(t, v);
}

Token::Token(int v) {
    this->setToken(_INTEGER, (void*)(new int(v)));
}

Token::Token(Type t) {
    this->type = t;
    switch(this->type) {
        case _INTEGER:
            this->value = (void*)(new int(0));
            break;
        case _PLUS:
            this->value = (void*)(new string("plus"));
            break;
        case _EOF:
            this->value = (void*)(new string("eof"));
            break;
    }
}

Type Token::getType() {
    return this->type;
}

void* Token::getValue() {
    return this->value;
}

int Token::getIntValue() {
    if (this->type == _INTEGER) {
        return *((int*) this->value);
    } else {
        return 0;
    }
}

void Token::setToken(Type t, void* v) {
    this->type = t;
    this->value = v;
}

string Token::stringRepresentation() {
    string sType;
    string sVal;

    switch(this->type) {
        case _INTEGER:
            sType = "_INTEGER";
            sVal = std::to_string(*((int*) this->value));
            break;
        case _PLUS:
            sType = "_PLUS";
            sVal = *((string*) this->value);
            break;
        case _EOF:
            sType = "_EOF";
            sVal = *((string*) this->value);
            break;
    }
    return "{" + sType + ": " + sVal + "}";
}