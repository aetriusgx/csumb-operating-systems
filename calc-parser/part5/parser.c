#include "lexer.h"
#include "error.h"
#include "expr.h"

//
// a predictive parser for a super-minimal programming language
//

// grammar:
//   expr  ::= NUM expr1 | (expr) expr1 
//   expr1 ::= + expr | - expr | ""

// types of functions used below
void match();
EXPR *parse();
EXPR *expr(), *expr1();

int lookahead;    // most recent token

// check that current token is t, and read next token
void match(int t) { 
  if (lookahead == t)
    lookahead = lexan();
  else error("syntax error");
} 

// parse an expression
EXPR *parse() {
  EXPR *e;
  lookahead = lexan();
  e = expr();
  match(DONE);
  return e;
}

// an arithmetic expression
EXPR *expr() {
  EXPR *e, *e1;
  int i;
  switch(lookahead) {
  case '(':
    match('(');
    e1 = expr();
    match(')');
    e = expr1(e1);
    return e;
  case NUM:
    i = lexer_num_val();
    // grammar:
    //   expr  ::= NUM expr1 | (expr) expr1 
    //   expr1 ::= + expr | - expr | ""
    match(NUM);
    e = expr_create_num(i);
    e = expr1(e);
    return e;
  default:
    error("syntax error");
  }
}
   
// an expression, after the initial NUM
EXPR *expr1(EXPR *e1) {
  EXPR *e2;
  switch(lookahead) {
  case '+':
    match('+');
    e2 = expr();
    return expr_create_sum(e1, e2);
  case '-':
    match('-');
    e2 = expr();
    return expr_create_diff(e1, e2);
  default:
    return e1;
  }
}
