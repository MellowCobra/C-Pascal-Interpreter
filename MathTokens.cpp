// Interprets tokens for math symbols
// Copyright (c) 2017 Grayson Dubois @mellowcobra

#include "MathTokens.h"

Token::Token() {
    this->setToken(_NULL);
}

Token::Token(Type t, void* v) {
    this->setToken(t, v);
}

Token::Token(int v) {
    this->setToken(_INTEGER, (void*)(new int(v)));
}

Token::Token(Type t) {
    this->setToken(t);
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

void Token::setToken(Type t) {
    this->type = t;
    switch(this->type) {
        case _INTEGER:
            this->value = (void*)(new int(0));
            break;
        case _PLUS:
            this->value = (void*)(new string("+"));
            break;
        case _MINUS:
            this->value = (void*)(new string("-"));
            break;
        case _EOF:
            this->value = (void*)(new string("eof"));
            break;
        case _NULL:
            this->value = (void*)(new int(0));
            break;
    }
}

string Token::stringRepresentation() const {
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
        case _MINUS:
            sType = "_MINUS";
            sVal = *((string*) this->value);
        case _EOF:
            sType = "_EOF";
            sVal = *((string*) this->value);
            break;
        case _NULL:
            sType = "_NULL";
            sVal = std::to_string(*((int*) this->value));
    }
    return "{" + sType + ": " + sVal + "}";
}