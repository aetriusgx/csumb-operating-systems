#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "expr.h"
#include "string_util.h"

// constructor for variable expression
// ID
EXPR* expr_create_var(char* s) {
   EXPR* e = (EXPR*) malloc(sizeof(EXPR));
   e->expr_type = VAR_EXPR;
   e->s = str_dup(s);
   return e;
}

// constructor for num expression
// NUM
EXPR* expr_create_num(int i) {
   EXPR* e = (EXPR*) malloc(sizeof(EXPR));
   e->expr_type = NUM_EXPR;
   e->i = i;
   return e;
}

// constructor for function call expression
// ID (expr)
EXPR* expr_create_fcall(char* fname, EXPR* expr) {
   EXPR* e = malloc(sizeof(EXPR));
   e->expr_type = FCALL_EXPR;
   e->s = str_dup(fname);
   e->expr = expr;
   return e;
}

// print this expression
void expr_print(EXPR* expr) {
   switch (expr->expr_type) {
      case VAR_EXPR:
         printf(expr->s);
         break;
      case NUM_EXPR:
         printf("%d", expr->i);
         break;
      case FCALL_EXPR:
         printf("%s(", expr->s);
         expr_print(expr->expr);
         printf(")");
         break;
      default:
         break;
   }
}


// GRAMMAR
// prog  ::= ID stmt1 ; prog1
// prog1 ::= ID stmt1 ; prog1 | ""
// stmt1 ::= ( expr ) | = expr
// expr  ::= ID ( expr ) | ID | NUM
