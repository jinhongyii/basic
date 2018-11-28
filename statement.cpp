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
    /* Empty */
}
statementtype Statement::gettype() {}

assignmentstmt::assignmentstmt(int value, string var) : value(value), var(std::move(var)) {
}

void assignmentstmt::execute(EvalState &state) {
    state.setValue(var, value);
}
statementtype assignmentstmt::gettype() {
    return assignment;
}
printstmt::printstmt(string var) : var(std::move(var)) {
}

void printstmt::execute(EvalState &state) {

    cout << state.getValue(var)<<endl;
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
    try {
        int temp;
        cin >> temp;
        state.setValue(var, temp);
    } catch (...) {
        error("INVALID NUMBER");
    }
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
    if (compare(condition, state)) {
        program.switchstmt(gotoline);
    }
}
statementtype IFstmt::gettype() {
    return IF;
}