#include <iostream>
#include <string>
#include "Errors.h"

using namespace std;

#include "Interpreter.h"

int main(int argc, char* argv[]) {

    string expressionToInterpret = "";
    cout << "Enter an expression to interpret: ";
    cin >> expressionToInterpret;

    Interpreter interpreter(expressionToInterpret);
    int result;
    try {
        result = interpreter.expr();
    } catch (ParsingException &e) {
        cout << e.what() << "\n";
        return 1;
    }

    cout << "result of " << expressionToInterpret << " is " << result << "\n";

    return 0;
}