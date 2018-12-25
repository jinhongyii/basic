#include <utility>
#include "tokenscanner.h"
#include "parser.h"
#include "exp.h"
/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "program.h"


using namespace std;

Program::Program() {
}

Program::~Program() {
    for (auto &stmt : stmts) {
        delete(stmt.second);
    }
}

void Program::clear() {
    lines.clear();
    stmts.clear();
}

void Program::addSourceLine(int lineNumber, string line) {
    lines[lineNumber] = std::move(line);
}

void Program::removeSourceLine(int lineNumber) {
    lines.erase(lineNumber);
}

string Program::getSourceLine(int lineNumber) {

    return lines[lineNumber];
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
    stmts[lineNumber]=stmt;
}

Statement *Program::getParsedStatement(int lineNumber) {

    return stmts[lineNumber];
}

int Program::getFirstLineNumber() {
    return lines.empty() ? -1 : (lines.begin())->first;
}


void Program::switchstmt(int lineno) {
    if (lines.find(lineno) == lines.end()) {
        error("LINE NUMBER ERROR");
    }
    current=lineno;
}
//execute from start to end
//special operations for statements that change current linenumber
void Program::execute(EvalState &state) {
    current=(*(stmts.begin())).first;
    for (auto i = stmts.begin(); i != stmts.end();) {
        current=(*i).first;
        int temp=current;
        (*i).second->execute(state);
        if ((*i).second->gettype() == ending) {
            break;
        }
        if ((*i).second->gettype() == Goto) {
            i=stmts.find(current);
            continue;
        }
        if ((*i).second->gettype() == IF) {
            if(temp!=current) {
                i = stmts.find(current);
                continue;
            }
        }
        i++;
    }
}
void Program::showlines() {
    for (auto i = lines.begin(); i != lines.end(); i++) {
        cout<<(*i).second<<endl;
    }
}
