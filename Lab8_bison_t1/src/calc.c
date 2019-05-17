/**
* Name: RoboticRice
* Lab: Lab 8 Bison - Part 1
* Date: 04/2/19
**/

#include "calc.h"

void yyerror(char *s) {
   printf("\nERROR: %s\n", s);
   // note stderr that normally defaults to stdout, but can be redirected: ./src 2> src.log
   // CLion will display stderr in a different color from stdin and stdout
}

/*
 * The function to resolve a name of a function; i.e., to translate it to an int equivalent (if possible)
 * that can be used conveniently in the src() function.
 */
int resolveFunc(char *func) {
   // all functions are exactly as they appear in math.h; use man to get details
   char *funcs[] = {"neg",
                    "abs",
                    "exp",
                    "sqrt",
                    "add",
                    "sub",
                    "mult",
                    "div", //DO NOT LET DIV BY 0
                    "remainder",
                    "log", //6% extra credit log take optional 2nd arg, log of (op1) by base (op2). if takes one arg, log(base e)
                    "pow",
                    "max",
                    "min",
                    ""};

   int i = 0;
   while (funcs[i][0] != '\0') {
      if (!strcmp(funcs[i], func))
         return i;

      i++;
   }
   yyerror("invalid function"); // paranoic -- should never happen
   return -1;
}

/*
 * The function to calculate simple math operation.
 *
 * The values of op1 and op2 may be omitted for functions that take one or no parameters.
 */
double calc(char *func, double op1, double op2) {
   double result;

   //Since this assumes valid input, it is OK for (add .25 5) to = 30, rather than 5.25, as a number starting with "." is invalid input

   switch (resolveFunc(func)) {
       case NEG:
           result = -op1;
           break;
       case ABS:
           result = fabs(op1);
           break;
       case EXP:
           result = exp(op1);
           break;
       case SQRT:
           result = sqrt(op1);
           break;
       case ADD:
           result = op1 + op2;
           break;
       case SUB:
           result = op1 - op2;
           break;
       case MULT:
           result = op1 * op2;
           break;
       case DIV:
           if (op2 == 0)
               result = NAN; //can not div by 0
           else
               result = op1 / op2;
           break;
       case REMAINDER:
           result = remainder(op1, op2);
           break;
       case LOG:
           if (isnan(op2)) { //technically, op2 can be NAN as a result from a function, rather than not being provided -- if it is the result, then the correct answer is to return NAN rather than attempt to LOG op1 (which might of been a correct result)
               result = log(op1); //natural log of op1
           } else if (op2 != 1) {
                result = log(op1) / log(op2); //this makes it log(base op2 of op1)
           } else
               result = NAN; //this is only if the user try's to div by log(1), which = 0
          break;
       case POW:
           result = pow(op1, op2);
          break;
       case MAX:
           result = fmax(op1, op2);
          break;
       case MIN:
           result = fmin(op1, op2);
          break;
      default:
         //should not need to be implemented
         result = NAN;
         break;
   }
   return result;

}  
