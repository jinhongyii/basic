//
// Created by jinho on 2018/11/27.
//

#include <cctype>
#include <iostream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "error.h"
#include "tokenscanner.h"
#include "simpio.h"
#include "strlib.h"
#include "statement.h"
using namespace std;
string keywords[] = {"LET", "IF", "INPUT", "PRINT", "END", "REM", "GOTO", "THEN", "RUN", "LIST", "CLEAR", "QUIT",
                     "HELP"};

bool find(string a) {
    for (auto i:keywords) {
        if (a == i) {
            return true;
        }
    }
    return false;
}


void processLine(string line, Program & program, EvalState & state);
int main(){
    EvalState state;
    Program program;
    //cout << "Stub implementation of BASIC" << endl;
    while (true) {
        try {
            processLine(getLine(), program, state);
        } catch (ErrorException & ex) {
            cerr << "Error: " << ex.getMessage() << endl;
        }
    }
}
void processLine(string line, Program & program, EvalState & state) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);
    /*while (scanner.hasMoreTokens()) {
        Expression *exp = readT(scanner);
        if(exp->getType()==CONSTANT) {
            int value = exp->eval(state);
            program.addSourceLine(value, line);
            cout << value << endl;
            delete exp;
        } else if()
    }*/
    Expression *exp=readE(scanner);
    cout<<exp->toString()<<endl;
    cout<<exp->getType()<<endl;
}