# Cpp-Pascal-Interpreter
An interpreter for the Pascal language written in C++ as an exercise on writing Interpreters.

Currently interprets one, multi digit addition or subtraction expression.
Ignores whitespace

Recognizes the following Token Types:
* _INTEGER - Integer values
* _PLUS    - The plus sign '+'
* _MINUS   - The minus sign '-'
* _MUL     - The multiplication sign '*'
* _DIV     - The division sign '/'
* _EOF     - Signifies the end of file
* _NULL    - An empty token which represents null values

Catches the following exceptions:
* ParsingException - Generic parsing error, describes the line and location of the error. All exceptions are derived from this one.
* UnknownTokenException - Thrown when the interpreter finds a character it does not recognize.
* UnmatchedTokenException - Thrown when the next token being parsed does not match the expected type.