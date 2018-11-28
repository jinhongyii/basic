//
// Created by jinho on 2018/11/27.
//

#include <cctype>
#include <iostream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"
#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
#include "statement.h"

using namespace std;
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