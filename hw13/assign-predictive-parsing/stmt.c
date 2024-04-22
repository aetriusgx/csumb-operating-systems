#include <stdio.h>
#include <stdlib.h>
#include "stmt.h"
#include "expr.h"
#include "string_util.h"

// constructor for assignment statement
// = expr
STMT* stmt_create_assign(char* var, EXPR* expr) {
   STMT* s = (STMT*) malloc(sizeof(STMT));
   s->stmt_type = ASSIGN_TYPE;
   s->id = str_dup(var);
   s->expr = expr;
   return s;
}

// constructor for call statement
// (expr)
STMT* stmt_create_call(char* fname, EXPR* expr) {
   STMT* s = (STMT*) malloc(sizeof(STMT));
   s->stmt_type = CALL_TYPE;
   s->id = str_dup(fname);
   s->expr = expr;
   return s;
}

// print this statement
void stmt_print(STMT* stmt) {
   switch (stmt->stmt_type) {
      case ASSIGN_TYPE:
         printf("%s = ", stmt->id);
         expr_print(stmt->expr);
         break;
      case CALL_TYPE:
         printf("%s(", stmt->id);
         expr_print(stmt->expr);
         printf(")");
         break;
      default:
         break;
   }
}
