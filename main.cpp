#include <iostream>
#include <fstream>
#include <string>
#include "Errors.h"

using namespace std;

#include "Interpreter.h"

int main(int argc, char* argv[]) {

    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    ifstream infile(filename);

    for (string line; getline(infile, line);) {
        Interpreter interpreter(line);
        int result;
        try {
            result = interpreter.expr();
        } catch (ParsingException &e) {
            cout << e.what() << "\n";
            return 1;
        }

        cout << "result of " << line << " is " << result << "\n";
    }

    return 0;
}