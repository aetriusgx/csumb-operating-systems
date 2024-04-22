#include <stdlib.h>
#include <stdio.h>
#include "parser.h"
#include "lexer.h"
#include "expr.h"

void main(int argc, char *argv[]) {

   // parse program
   lexer_init();
   EXPR *expr = parse();

   // pretty-print program
   expr_print(expr);
   printf("\n");

   exit(EXIT_SUCCESS);
}
