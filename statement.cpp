#include <utility>

#include <utility>

#include <utility>

/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */
bool endingflag=false;
#include <string>

#include "statement.h"

using namespace std;

/* Implementation of the Statement class */

Statement::Statement() {
    /* Empty */
}

Statement::~Statement() {
}
statementtype Statement::gettype() {}

assignmentstmt::assignmentstmt(Expression *exp, string var) :exp(exp),var(var){}



void assignmentstmt::execute(EvalState &state) {
    state.setValue(var, exp->eval(state));
}
statementtype assignmentstmt::gettype() {
    return assignment;
}
printstmt::printstmt(Expression *exp):exp(exp) {

}

void printstmt::execute(EvalState &state) {

    cout << exp->eval(state)<<endl;
}
statementtype printstmt::gettype() {
    return print;
}
commentstmt::commentstmt() = default;

void commentstmt::execute(EvalState &state) {}
statementtype commentstmt::gettype() {
    return comment;
}
inputstmt::inputstmt(string var) : var(std::move(var)) {}

void inputstmt::execute(EvalState &state) {

    bool correct=false;
    do {
        try {
            string temp;
            cout<<" ? ";
            getline(cin,temp);
            int num = stringToInteger(temp);
            state.setValue(var, num);
            correct=true;
        } catch (...) {
            cout<<"INVALID NUMBER"<<endl;
        }
    } while (!correct);
    //cin.get();
}
statementtype inputstmt::gettype() {
    return input;
}
endstmt::endstmt() = default;

void endstmt::execute(EvalState &state) {
    endingflag = true;
}
statementtype endstmt::gettype() {
    return ending;
}
Gotostmt::Gotostmt(int lineno, Program &program) : lineno(lineno), program(program) {}

void Gotostmt::execute(EvalState &state) {
    program.switchstmt(lineno);
}
statementtype Gotostmt::gettype() {
    return Goto;
}

IFstmt::IFstmt(Expression *condition, int gotoline,Program&program):condition(condition),gotoline(gotoline),program(program) {
}
void IFstmt::execute(EvalState &state) {
    if (condition->eval(state)) {
        program.switchstmt(gotoline);
    }
}
statementtype IFstmt::gettype() {
    return IF;
}
emptystmt::emptystmt() {}
void emptystmt::execute(EvalState &state) {}
statementtype emptystmt::gettype() {
    return empty;
}