#include <stdlib.h>
#include <stdio.h>
#include "expr.h"

// build expression objects

void main(int argc, char *argv[]) {

   // create expression 3 + 4
   EXPR *e1 = expr_create_num(3);
   EXPR *e2 = expr_create_num(4);
   EXPR *e = expr_create_sum(e1, e2);

   // create expression 3 + 4 - 1
   // YOUR CODE HERE
   EXPR *s1 = expr_create_num(1);
   EXPR *s = expr_create_diff(e, s1);

   exit(EXIT_SUCCESS);
}
