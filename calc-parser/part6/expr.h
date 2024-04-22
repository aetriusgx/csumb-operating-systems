#ifndef EXPR_INC
#define EXPR_INC

// an expression
//
// An expression can be a variable, a number, or a 
// function call.  I use a hack so that this "class"
// can capture all kinds of expressions.

// valid expression types
#define NUM_EXPR 0       
#define SUM_EXPR 1       
#define DIFF_EXPR 2     

// A C union could have been used here if storage were important
typedef struct expr {
   int expr_type;        
   int i;                // for num
   struct expr *expr1;   // for arith. operators
   struct expr *expr2;   // for arith. operators
} EXPR;

EXPR *expr_create_num(int i);
EXPR *expr_create_sum(EXPR *expr1, EXPR *expr2);
EXPR *expr_create_diff(EXPR *expr1, EXPR *expr2);
int   expr_eval(EXPR *expr);
void  expr_print(EXPR *expr);
#endif


