//
// Created by jinho on 2018/11/27.
//

#include "calculate.h"
//处理不等式的结果
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