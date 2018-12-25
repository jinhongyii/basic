/*
 * File: Basic.cpp
 * ---------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 * [TODO: extend and correct the documentation]
 */

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

using namespace std;

/* Function prototypes */
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
//detect error and process lines according to its type(beginning with number or word)
void processLine(string line, Program &program, EvalState &state);

/* Main program */
bool flag = false;

int main() {
    EvalState state;
    Program program;

    while (true) {
        try {
            processLine(getLine(), program, state);
            if (flag) {
                return 0;
            }

        } catch (ErrorException &ex) {
            cout << ex.getMessage() << endl;


        }
    }
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(string line, Program &program, EvalState &state) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);
    int lineno;

    Expression *exp = readE(scanner);
    //has linenumber
    if (exp->getType() == CONSTANT) {
        int value = exp->eval(state);
        lineno = value;
        delete exp;
        if (!scanner.hasMoreTokens()) {
            program.removeSourceLine(lineno);
            return;
        }
        //judge what kind of statement to add
        exp = readE(scanner);
        if (exp->toString() == "LET") {
            Expression *exp2 = readE(scanner);
            if (scanner.hasMoreTokens()) {
                error("SYNTAX ERROR");
            }
            auto l = ((CompoundExp *) exp2)->getLHS();
            auto r = ((CompoundExp *) exp2)->getRHS();
            if (l->getType() != IDENTIFIER or find(l->toString())) {
                error("SYNTAX ERROR");
            }
            Statement *temp = new assignmentstmt(r, l->toString());
            program.setParsedStatement(lineno, temp);
            program.addSourceLine(lineno, line);
            delete exp;
            return;
        } else if (exp->toString() == "INPUT") {
            Expression *exp2 = readE(scanner);
            if (scanner.hasMoreTokens() or find(exp2->toString()) or exp2->getType() != IDENTIFIER) {
                error("INVALID NUMBER");
            }

            Statement *temp = new inputstmt(exp2->toString());
            program.setParsedStatement(lineno, temp);
            program.addSourceLine(lineno, line);
            delete exp;
            return;
        } else if (exp->toString() == "PRINT") {
            Expression *exp2 = readE(scanner);
            if (scanner.hasMoreTokens()) {

                error("SYNTAX ERROR");
            }

            Statement *temp = new printstmt(exp2);
            program.setParsedStatement(lineno, temp);
            program.addSourceLine(lineno, line);
            delete exp;
            return;
        } else if (exp->toString() == "REM") {
            Statement *temp = new commentstmt();
            program.setParsedStatement(lineno, temp);
            program.addSourceLine(lineno, line);
            delete exp;
            return;
        } else if (exp->toString() == "END") {
            if (scanner.hasMoreTokens()) {

                error("SYNTAX ERROR");
            }
            Statement *temp = new endstmt();
            program.setParsedStatement(lineno, temp);
            program.addSourceLine(lineno, line);
            delete exp;
            return;
        } else if (exp->toString() == "GOTO") {
            Expression *exp2 = readE(scanner);
            if (scanner.hasMoreTokens() or exp2->getType() != CONSTANT) {

                error("SYNTAX ERROR");
            }

            Statement *temp = new Gotostmt(exp2->eval(state), program);
            program.setParsedStatement(lineno, temp);
            program.addSourceLine(lineno, line);
            delete exp;

            return;
        } else if (exp->toString() == "IF") {
            Expression *exp2 = readE(scanner);
            auto op = ((CompoundExp *) exp2)->getOp();
            Expression *exp3 = readE(scanner);
            if (op != ">" and op != "<" and op != "=" and exp3->toString() != "THEN") {
                error("SYNTAX ERROR");
            }
            exp3 = readE(scanner);
            if (exp3->getType() != CONSTANT or scanner.hasMoreTokens()) {
                error("SYNTAX ERROR");
            }
            Statement *temp = new IFstmt(exp2, exp3->eval(state), program);
            program.setParsedStatement(lineno, temp);
            program.addSourceLine(lineno, line);
            delete exp;
            return;
        }
        delete exp;
        error("SYNTAX ERROR");
    } else if (exp->getType() == IDENTIFIER) {//doesn't have linenumber
        if (exp->toString() == "RUN") {
            if (scanner.hasMoreTokens()) {
                error("SYNTAX ERROR");
            }
            program.execute(state);
            delete exp;
            return;
        } else if (exp->toString() == "LIST") {
            if (scanner.hasMoreTokens()) {
                error("SYNTAX ERROR");
            }
            program.showlines();
            delete exp;
            return;
        } else if (exp->toString() == "CLEAR") {
            if (scanner.hasMoreTokens()) {
                error("SYNTAX ERROR");
            }
            program.clear();
            state.clear();
            delete exp;
            return;
        } else if (exp->toString() == "QUIT") {
            if (scanner.hasMoreTokens()) {
                error("SYNTAX ERROR");
            }
            flag = true;
            delete exp;
            return;
        } else if (exp->toString() == "HELP") {
            if (scanner.hasMoreTokens()) {
                error("SYNTAX ERROR");
            }
            cout << "Yet another basic interpreter" << endl;
            delete exp;
            return;
        } else if (exp->toString() == "LET") {
            Expression *exp2 = readE(scanner);
            if (scanner.hasMoreTokens()) {
                error("SYNTAX ERROR");
            }
            auto l = ((CompoundExp *) exp2)->getLHS();
            auto r = ((CompoundExp *) exp2)->getRHS();
            if (l->getType() != IDENTIFIER or find(l->toString())) {
                error("SYNTAX ERROR");
            }
            state.setValue(l->toString(), r->eval(state));
            delete exp;
            return;
        } else if (exp->toString() == "PRINT") {
            Expression *exp2 = readE(scanner);
            if (scanner.hasMoreTokens()) {
                error("SYNTAX ERROR");
            }
            cout << exp2->eval(state) << endl;
            delete exp;
            return;
        } else if (exp->toString() == "INPUT") {
            Expression *exp2 = readE(scanner);
            if (scanner.hasMoreTokens()) {
                error("SYNTAX ERROR");
            }
            bool correct=false;
            do {
                try {
                    string temp;
                    cout<<" ? ";
                    getline(cin,temp);
                    int num = stringToInteger(temp);
                    state.setValue(exp2->toString(), num);
                    correct=true;
                } catch (...) {
                    cout<<"INVALID NUMBER"<<endl;
                }
            } while (!correct);
            delete exp;
            return;
        }
        delete exp;
        error("SYNTAX ERROR");
    }
}
