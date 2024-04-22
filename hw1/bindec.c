#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// max length input string
#define MAXSTR 25

// convert input binary string to a number

int main() {

   // user input string
   char s[MAXSTR+3]; 

   // prompt for input
   printf("> ");

   // read input string; at most MAXSTR+1 chars accepted
   // Note: this is tricky. If we accept only MAXSTR chars,
   // we can't see if user entered more chars and they are
   // being dropped by fgets.
   fgets(s, MAXSTR+3, stdin);

   // check input length; n does not include final carriage return
   int n = strlen(s)-1;  
   if (n > MAXSTR) {
     printf("input cannot be more than %d characters\n", MAXSTR);
     exit(1);
   }

   // convert s from a string in binary, to an int, and output
   
   // YOUR CODE HERE 
   int val = 0;
   for (int i = n-1; i >= 0; i--) {
      if (s[i] == '1') {
         val += pow(2, n-i-1);
      }
   }
   
   printf("%d", val);
   
   return 0;
}

