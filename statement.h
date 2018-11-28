/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface specified in Chapter 17, which is an
 * excellent model for the Statement class hierarchy.
 */

#ifndef _statement_h
#define _statement_h
class Program;

#include "evalstate.h"
#include "exp.h"
#include "program.h"
#include "calculate.h"
#include "tokenscanner.h"
#include "parser.h"
#include "strlib.h"
/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */
enum statementtype {assignment,print,comment,input,ending,Goto,IF,empty};
class Statement {

public:

/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

   Statement();

/*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

   virtual ~Statement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */

   virtual void execute(EvalState & state) = 0;
   virtual statementtype gettype();
};


/*
 * The remainder of this file must consists of subclass
 * definitions for the individual statement forms.  Each of
 * those subclasses must define a constructor that parses a
 * statement from a scanner and a method called execute,
 * which executes that statement.  If the private data for
 * a subclass includes data allocated on the heap (such as
 * an Expression object), the class implementation must also
 * specify its own destructor method to free that memory.
 */
class assignmentstmt: public Statement {
private:
    int value;
    string var;
public:
    assignmentstmt(int value,string var);
    virtual void execute(EvalState & state);
    virtual statementtype gettype();
};

class printstmt :public Statement{
private:
    Expression* exp;
public:
    printstmt(Expression* exp);
    virtual void execute(EvalState & state);
    virtual statementtype gettype();
};

class commentstmt :public Statement {
public:
    commentstmt();
    virtual void execute(EvalState & state);
    virtual statementtype gettype();
};

class inputstmt :public Statement {
private:
    string var;
public:
    inputstmt(string var);
    virtual void execute(EvalState & state);
    virtual statementtype gettype();
};

class endstmt:public Statement {
public:
    endstmt();
    virtual void execute(EvalState & state);
    virtual statementtype gettype();
};

class Gotostmt:public Statement {
private:
    int lineno;
    Program & program;
public:
    Gotostmt(int lineno,Program& program);
    virtual void execute(EvalState & state);
    virtual statementtype gettype();
};

class IFstmt:public Statement {
private:
    Expression* condition;
    int gotoline;
    Program & program;
public:
    IFstmt(Expression* condition,int gotoline,Program & program);
    virtual void execute(EvalState & state);
    virtual statementtype gettype();
};
class emptystmt:public Statement{
public:
    emptystmt();
    virtual void execute(EvalState & state);
    virtual statementtype gettype();
};
#endif
