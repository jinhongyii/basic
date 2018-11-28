//
// Created by jinho on 2018/11/27.
//

#include "calculate.h"
/*int calculate(Expression* exp){
    if (exp->getType() == IDENTIFIER) {
        return exp->eval()；
    } else if (exp->getType()==CONSTANT) {
        return exp->eval();
    }
    auto l=((CompoundExp*)exp)->getLHS();
    auto r=((CompoundExp*)exp)->getRHS();
    auto op=((CompoundExp*)exp)->getOp();
    if (op == "+") {
        return calculate(l)+calculate(r);
    } else if (op == "-") {
        return calculate(l)-calculate(r);
    } else if (op == "*") {
        return calculate(l)*calculate(r);
    } else if (op == "/") {
        return calculate(l)/calculate(r);
    }
}*/
bool compare(Expression *exp,EvalState&state){
    auto l=((CompoundExp*)exp)->getLHS();
    auto r=((CompoundExp*)exp)->getRHS();
    auto op=((CompoundExp*)exp)->getOp();
    if (op == ">") {
        return l->eval(state)>r->eval(state);
    } else if (op == "<") {
        return r->eval(state)>l->eval(state);
    } else if (op == "=") {
        return l->eval(state)==r->eval(state);
    }
    error("SYNTAX ERROR");
}