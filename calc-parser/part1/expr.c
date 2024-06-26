#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "expr.h"

// original grammar:
//   expr ::= NUM | expr + expr | expr - expr | (expr)
//
// transformed grammar:
//   expr  ::= NUM expr1 | (expr) expr1 
//   expr1 ::= + expr | - expr | ""

// constructor for num expression
EXPR *expr_create_num(int i) {
  EXPR *e = malloc(sizeof(EXPR));
  e->expr_type = NUM_EXPR;
  e->i = i;
  return e;
}

// constructor for sum expression
EXPR *expr_create_sum(EXPR *expr1, EXPR *expr2) {
  EXPR *e = malloc(sizeof(EXPR));
  e->expr_type = SUM_EXPR;
  e->expr1 = expr1;
  e->expr2 = expr2;
  return e;
}

// constructor for diff expression
EXPR *expr_create_diff(EXPR *expr1, EXPR *expr2) {

  EXPR* e = malloc(sizeof(EXPR));
  e->expr_type = DIFF_EXPR;
  e->expr1 = expr1;
  e->expr2 = expr2;

  return e;
}

