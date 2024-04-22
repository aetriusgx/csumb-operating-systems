#include <stdlib.h>
#include <stdio.h>
#include "expr.h"

// build and print expression objects

void main(int argc, char *argv[]) {

   // create expression 3 + 4
   EXPR *e1 = expr_create_num(3);
   EXPR *e2 = expr_create_num(4);
   EXPR *e = expr_create_sum(e1, e2);
   expr_print(e);
   printf("\n");

   // create expression 3 + 4 - 1
   // YOUR CODE HERE
   e1 = expr_create_num(3);
   e2 = expr_create_num(4);
   EXPR *e3 = expr_create_num(1);
   e = expr_create_diff(expr_create_sum(e1, e2), e3);
   expr_print(e);
   printf("\n");

   exit(EXIT_SUCCESS);
}
