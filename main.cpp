#include <iostream>
#include <string>

using std::cout;

#include "MathTokens.h"
#include "Interpreter.h"

int main(int argc, char* argv[]) {

    Token t1(42);
    Token t2(_PLUS);
    Token t3(_EOF);

    cout << "t1 is " << t1.stringRepresentation() << "\n";
    cout << "t2 is " << t2.stringRepresentation() << "\n";
    cout << "t3 is " << t3.stringRepresentation() << "\n";

    return 0;
}