#include "lexer.h"
#include "error.h"
#include "expr.h"
#include "stmt.h"
#include "prog.h"

//
// a predictive parser for a super-minimal programming language
//
// refer to the BNF  

// types of functions used below
void match();
PROG* parse(), * prog(), * prog1();
STMT* stmt1();
EXPR* expr();

int lookahead;    // most recent token

// check that current token is t, and read next token
void match(int t) {
    if (lookahead == t)
        lookahead = lexan();
    else error("syntax error");
}

// parse a program
PROG* parse() {
    PROG* p;
    lookahead = lexan();
    p = prog();
    match(DONE);
    return p;
}

// one or more statements
PROG* prog() {
    // ::= ID stmt1 ; prog1

    // EXPR* expr = expr_create_fcall("printf", expr_create_num(22));
    // STMT* stmt = stmt_create_assign("x", expr);
    // PROG* prog = prog_create(stmt, NULL);
    if (lookahead == ID) {
        EXPR* var_ID = expr_create_var(lexer_id_val());
        match(ID);

        STMT* var_stmt1 = stmt1(var_ID->s);

        PROG* var_prog1, * prog_return;

        if (lookahead == ';') {
            match(';');
            var_prog1 = prog1();
            prog_return = prog_create(var_stmt1, var_prog1);
            return prog_return;
        }

        error("syntax error");
    }

    return prog_create(NULL, NULL);
}

PROG* prog1() {
    // ::= ID stmt1 ; prog1 | ""

    PROG* prog_ret;

    if (lookahead == ID) {
        // ID
        EXPR* ID_var = expr_create_var(lexer_id_val());
        match(ID);
        // stmt1
        STMT* stmt1_var = stmt1(ID_var->s);

        PROG* prog1_var;

        // ; 
        if (lookahead == ';') {
            match(';');
            // prog1
            prog1_var = prog1();

            prog_ret = prog_create(stmt1_var, prog1_var);
            return prog_ret;
        }
    }

    // ""
    if (lexer_num_val() == NONE) {
        return prog_create(NULL, NULL);
    }

    error("syntax error");
}

STMT* stmt1(char* id) {
    // ::= ( expr ) | = expr
    STMT* stmt_return;
    EXPR* var_expr;

    // = expr
    if (lookahead == '=') {
        match('=');
        // assignment statement
        var_expr = expr();
        stmt_return = stmt_create_assign(id, var_expr);

        return stmt_return;
    }

    // (expr)
    if (lookahead == '(') {
        // call statement
        match('(');
        var_expr = expr();
        stmt_return = stmt_create_call(id, var_expr);
        match(')');

        return stmt_return;
    }

    error("syntax error");
}

EXPR* expr() {
    EXPR* expr_return;
    // ::= ID ( expr ) | ID | NUM

    if (lookahead == NUM) {
        expr_return = expr_create_num(lexer_num_val());
        match(NUM);
        return expr_return;
    }

    if (lookahead == ID) {
        EXPR* expr_id = expr_create_var(lexer_id_val());

        match(ID);

        // 
        if (lookahead == '(') {
            match('(');
            EXPR* expr_var = expr();
            expr_return = expr_create_fcall(expr_id->s, expr_var);
            match(')');
            return expr_return;
        }

        // ID
        expr_return = expr_create_var(expr_id->s);

        return expr_return;
    }

    return expr_return;
}

// GRAMMAR
// prog ::= ID stmt ; prog | ""
// stmt ::= ( expr ) | = expr
// expr  ::= ID ( expr ) | ID | NUM









