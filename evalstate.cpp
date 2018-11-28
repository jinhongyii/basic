/*
 * File: evalstate.cpp
 * -------------------
 * This file implements the EvalState class, which defines a symbol
 * table for keeping track of the value of identifiers.  The public
 * methods are simple enough that they need no individual documentation.
 */

#include <string>
#include "evalstate.h"

#include "map.h"
using namespace std;

/* Implementation of the EvalState class */

EvalState::EvalState() {
   /* Empty */
}

EvalState::~EvalState() {
   /* Empty */
}
bool find(string a);

void EvalState::setValue(string var, int value) {
    if (find(var)) {
        error("SYNTAX ERROR");
    }
   symbolTable.put(var, value);
}

int EvalState::getValue(string var) {
    if (!isDefined(var)) {
        error("VARIABLE NOT DEFINED");
    }
   return symbolTable.get(var);
}

bool EvalState::isDefined(string var) {
   return symbolTable.containsKey(var);
}
void EvalState::clear() {
   symbolTable.clear();
}
