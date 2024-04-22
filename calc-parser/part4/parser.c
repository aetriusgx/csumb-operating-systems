#include <stdio.h>
#include "lexer.h"
#include "error.h"
#include "expr.h"

//
// a predictive parser for arithmetic expressions
//
// refer to the BNF  

// types of functions used below
void match();
void parse();
void expr(), expr1();

int lookahead;    // most recent token

// check that current token is t, and read next token
void match(int t) { 
  if (lookahead == t)
    lookahead = lexan();
  else error("syntax error");
} 

// parse an expression
void parse() {
  lookahead = lexan();
  expr();
  match(DONE);
}

// an arithmetic expression
void expr() {
  switch(lookahead) {
  case '(':
    match('(');
    expr();
    // YOUR CODE HERE (two lines of code)
    match(')');
    expr1();
    return;
  case NUM:
    match(NUM);
    expr1();
    return;
  default:
    error("syntax error");
  }
}
   
// an expression, after the initial NUM
void expr1() {
  switch(lookahead) {
  case '+':
    match('+');
    expr();
    return;
  case '-':
    // YOUR CODE HERE (two lines of code)
    match('-');
    expr();
    return;
  default:
    return;
  }
}

