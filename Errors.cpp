// Provides implementation for errors and exceptions
// that can be thrown by the Interpreter
// Copyright (c) 2017 Grayson Dubois @mellowcobra

#include "Errors.h"

ParsingException::ParsingException(const int& lin, const int& loc)
    : line(lin), location(loc) {}

const char* ParsingException::what() const throw() {
    return ("Parsing exception occured at line " + 
            to_string(this->line) + " at location " + 
            to_string(this->location)).c_str();
}


UnknownTokenException::UnknownTokenException(const int& lin, const int& loc, const char& ch)
    : ParsingException(lin, loc), character(ch) {}

const char* UnknownTokenException::what() const throw() {
    return (string(ParsingException::what()) + 
        string(": Unknown Token '" + string(1, this->character) + "'")
    ).c_str();
}


UnmatchedTokenException::UnmatchedTokenException(const int& lin, const int& loc, Token t1, Token t2)
    : ParsingException(lin, loc), currentToken(t1), expectedToken(t2) {}

const char* UnmatchedTokenException::what() const throw() {
    return (string(ParsingException::what()) +
        ": Unmatched Token - expected " + this->expectedToken.stringRepresentation() + ", but found " + 
        this->currentToken.stringRepresentation() + " instead"
    ).c_str();
}