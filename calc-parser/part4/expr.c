#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "expr.h"
#include "string_util.h"

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
  EXPR *e = malloc(sizeof(EXPR));
  e->expr_type = DIFF_EXPR;
  e->expr1 = expr1;
  e->expr2 = expr2;
  return e;
}

// print this expression
void expr_print(EXPR *expr) {
  switch(expr->expr_type) {
  case NUM_EXPR:
    printf("%d", expr->i);
    break;
  case SUM_EXPR:
    expr_print(expr->expr1);
    printf(" + ");
    expr_print(expr->expr2);
    break;
  case DIFF_EXPR:
    expr_print(expr->expr1);
    printf(" - ");
    expr_print(expr->expr2);
    break;
  default:
    printf("error: expr_print, bad expr type: %d\n", expr->expr_type);
    exit(EXIT_FAILURE);
  }
}

